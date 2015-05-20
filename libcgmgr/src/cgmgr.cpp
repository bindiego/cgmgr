#include <cstdlib>
#include <stdio.h>
#include <iostream>
//#include <errno.h>
//#include <sys/stat.h>
//#include <sys/types.h>
#include <cgmgr.h>

/*
 * @Author: Bin Wu
 * @Date: 21/Sep/2013
 */

using namespace std;

/* default constructor */
CgManager::CgManager(void){}

void CgManager::do_copy(const CgManager& obj){}

string CgManager::get_pclose_rtn_str(const int rtn_pclose) 
{
    // The returnvalue of the child process is in the top 16 bits. 
    // You have to divide the returned value of pclose by 256, 
    // then you get the searched return value of the child process.
    return to_string(rtn_pclose / 256);
}

/* copy constructor */
CgManager::CgManager(const CgManager& obj)
{
    this->do_copy(obj);
}

/* assignment operator */
CgManager& CgManager::operator=(const CgManager& obj)
{
    // check self-assignment
    if (this == &obj)
        return *this;

    this->do_copy(obj);
    
    return *this;
}

/* destructor */
CgManager::~CgManager(void){}

/* Utilities */
int CgManager::get_rtn_code(const string& str)
{
    int rtn = 0;

    size_t index = str.find(FULL_RTN_DEL);

    if (index != string::npos)
    {
        string val = str.substr(0, index);

        rtn = stoi(val);
    }

    return rtn;
}

string CgManager::get_rtn_output(const string& str)
{
    string rtn = "";

    size_t index = str.find(FULL_RTN_DEL);

    if (index != string::npos)
    {
        string val = str.substr(++index, string::npos);

        rtn = val;
    }

    return rtn;
}

/* functions */
string CgManager::exec_cmd(const string& cmd)
{
    FILE* pipe = popen((cmd + CMD_TRAILER_STDOUT).c_str(), "r");
    if (!pipe)
        return "-1,failed to run " + cmd;

    char buffer[BUFFER_SIZE];

    string str_out = "";

    while(!feof(pipe))
    {
        if (fgets(buffer, BUFFER_SIZE, pipe) != NULL)
            str_out += buffer;
    }

    return this->get_pclose_rtn_str(pclose(pipe)) + "," + str_out;
}

/* Old impl with return code ONLY
int CgManager::ls(const string opts)
{
    string cmd = "ls ";

    if (!opts.empty())
        cmd += "-" + opts;

    return system(cmd.c_str());
}
*/
string CgManager::ls(const string& opts)
{
    string cmd = "ls ";

    if (!opts.empty())
        cmd += "-l" + opts;

    return this->exec_cmd(cmd);
}

string CgManager::which(const string& pg)
{
    string cmd = "which ";

    if (!pg.empty())
        cmd += pg;
    else
        return "1,empty program name";

    return this->exec_cmd(cmd);
}

// cgroup calls
string CgManager::cg_list(void)
{
    string cmd = "lssubsys -am";

    return this->exec_cmd(cmd);
}

string CgManager::cg_create_hierarchy(
    const string& subsys,
    const string& path
) 
{
    // FIXME: syscalls later
    // int mkdir(const char *pathname, mode_t mode); 

    if (subsys.empty() || path.empty())
        return "1,subsys or path cannot be empty";

    string cmd = "";
    string exec_rtn = "";

    // create the directory
    cmd = "mkdir " + path;
    exec_rtn = this->exec_cmd(cmd);
    if (this->get_rtn_code(exec_rtn) != 0)
        return exec_rtn;

    // mount the file system
    cmd = "mount -t " + CG_MOUNT_TYPE +
        " -o " + subsys + " - " + path;
    exec_rtn = this->exec_cmd(cmd);
    if (this->get_rtn_code(exec_rtn) != 0)
        return exec_rtn;

    return "0,Hierarchy has been created with subsystems " 
        + subsys + " attached.";
}

string CgManager::cg_create_group(
    const string& subsys,
    const string& path,
    const string& scheduler,
    const string& admin
)
{
    if (subsys.empty() || path.empty())
        return "1,subsys or path cannot be empty";

    string cmd = "cgcreate ";

    if (!scheduler.empty())
        cmd += "-t " + scheduler + " ";

    if (!admin.empty())
        cmd += "-a " + admin + " ";

    cmd += "-g " + subsys + ":" + path;

    return this->exec_cmd(cmd);
}

string CgManager::cg_del_group(
    const string& subsys,
    const string& path
)
{
    if (subsys.empty() || path.empty())
        return "1,subsys or path cannot be empty";

    string cmd = "cgdelete " +
        subsys + ":" + path;

    return this->exec_cmd(cmd);
}

string CgManager::cg_set_value(
    const string& parameter,
    const string& value,
    const string& path
)
{
    if (parameter.empty() || value.empty())
        return "1,path or value cannot be empty";

    string cmd = "cgset -r " +
        parameter + "=" + value + " " +
        path;

    return this->exec_cmd(cmd);
}

string CgManager::cg_set_copy(
    const string& from_group,
    const string& to_group
)
{
    if (from_group.empty() || to_group.empty())
        return "1,both groups cannot be empty";

    string cmd = "cgset --copy-from " +
        from_group + " " + to_group;

    return this->exec_cmd(cmd);
}

string CgManager::cg_classify(
    const string& subsys,
    const string& path,
    const string& pidlist
)
{
    if (subsys.empty() || path.empty() || pidlist.empty())
        return "1,parameters passed in cannot be empty";

    string cmd = "cgclassify -g " +
        subsys + ":" + path + " " +
        pidlist;

    return this->exec_cmd(cmd);
}

string CgManager::cg_exec(
    const string& subsys,
    const string& path,
    const string& cmd,
    const string& opts
)
{
    if (subsys.empty() || path.empty() || opts.empty())
        return "1,subsystems, path or opts is empty";

    string full_cmd = "cgexec -g " +
        subsys + ":" + path + " " +
        cmd;

    if (!opts.empty())
        full_cmd += " " + opts;

    return this->exec_cmd(full_cmd);
}
