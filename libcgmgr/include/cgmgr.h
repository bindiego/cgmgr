#ifndef CG_MGR_H
#define CG_MGR_H

#include <string>

static const int BUFFER_SIZE = 512;
static const std::string CMD_TRAILER_NONE = " > /dev/null 2>&1";
static const std::string CMD_TRAILER_STDOUT = " 2>&1";
static const std::string FULL_RTN_DEL = ",";
static const std::string CG_MOUNT_TYPE = "cgroup";

/*
 * @Author: Bin Wu
 * @Date: 21/Sep/2013
 * @Desc:
 */

class CgManager
{
    public:
        /* std constructor */
        CgManager(void);

        /* copy constructor */
        CgManager(const CgManager& obj);

        /* assignment operator */
        CgManager& operator=(const CgManager& obj);

        /* destructor */
        ~CgManager(void);

        // Utilities
        /*
         * Get the return code as integer from the full returning string
         */
        int get_rtn_code(const std::string& str);

        /*
         * Get the output text, includes stderr, from the full returning string
         */
        std::string get_rtn_output(const std::string& str);

        /* system functions */
        // not system calls but exec shell cmds, returning
        // string consists of "<return code>,<stdout+stderr>" for 
        // easy JNI parsing. Same for cgroup calls, requires
        // libcgroup or cgroup-bin in Ubuntu for example
        /*
         * @param run a command in *nix
         */
        std::string exec_cmd(const std::string& cmd = std::string(""));

        /*
         * @param options for ls
         *
         * e.g. "lha" => "ls -lha"
         */
        std::string ls(const std::string& opts = std::string(""));

        /*
         * @param options for which, compulsory 
         * e.g. "ls" => "which ls"
         */
        std::string which(const std::string& pg = std::string(""));

        // cgroup calls
        /*
         * List system supported subsystems and mount point
         */
        std::string cg_list(void);

        /*
         * @param subsystems, delimited by ','
         *        e.g. "cpu" or "cpu,cpuset,memory"
         * @param path, system mount path
         *        e.g. "/sys/fs/cgroup/cpu" or "/sys/fs/cgroup/cpu-n-mem"
         */
        std::string cg_create_hierarchy(
            const std::string& subsys = std::string(""),
            const std::string& path = std::string("")
        );

        /*
         * @param subsystems, delimited by ','
         *        e.g. "cpu"
         * @param path, this is actually the name of the group
         *        e.g. "/group-cpu-0", will create a group called "group-cpu-0"
         *        at /sys/fs/cgroup/cpu/group-cpu-0, then you can configure it
         *        to only use core 0 for example.
         * @param scheduler, format "uid:gid", indicates the owner of the tasks
         *        pseudo-file for this group. This user can add tasks to the
         *        cgroup. (Optional, default is same as parent cgroup)
         * @param admin, format "uid:gid", indicates the owner of all the 
         *        pseudo-files other than tasks for this group. This user can
         *        modify the access that the tasks in this cgroup use 
         *        system resources. (Optional, default is same as parent 
         *        cgroup.)
         */
        std::string cg_create_group(
            const std::string& subsys = std::string(""),
            const std::string& path = std::string(""),
            const std::string& scheduler = std::string(""),
            const std::string& admin = std::string("")
        );

        /*
         * @param subsystems, delimited by ','
         *        e.g. "cpu"
         * @param path, this is actually the name of the group
         *        e.g. "/group-cpu-0", will delete a group called "group-cpu-0"
         *        at /sys/fs/cgroup/cpu/group-cpu-0
         */
        std::string cg_del_group(
            const std::string& subsys = std::string(""),
            const std::string& path = std::string("")
        );

        /*
         * @param this is the parameter to be set, which corresponds to the file
         *        in the directory of the given group.
         *        e.g. "cpuset.cpus"
         * @param this is the value of the parameter.
         *        e.g. "0"
         * @param this is the path to the cgroup relative to the root of the 
         *        hierarchy. Optional, default is root group.
         *        e.g. "/" or "." is the root group itself,
         *             OR "group-cpu-0"
         *
         *        NOTE: Only a small number of parameters can be set for 
         *        the root group (such as the cpuacct.usage parameter. 
         *        This is because a root group owns all of the existing 
         *        resources, therefore, it would make no sense to limit all 
         *        existing processes by defining certain parameters, for 
         *        example the cpuset.cpu parameter.
         */
        std::string cg_set_value(
            const std::string& parameter = std::string(""),
            const std::string& value = std::string(""),
            const std::string& path = std::string("/")
        );

        /*
         * @param path to the cgroup whose parameters are to be copied,
         *        relative to the root group of the hierarchy.
         *        e.g. "group-mem1-1024/"
         * @param path to the destination cgroup, relative to the root group
         *        of the hierarchy.
         *        e.g. "group-mem2-1024/"
         */
        std::string cg_set_copy(
            const std::string& from_group = std::string(""),
            const std::string& to_group = std::string("")
        );

        /*
         * @param subsys is a comma-separated list of subsystems, or * 
         *        to launch the process in the hierarchies associated with all 
         *        available subsystems. Note that if cgroups of the same name 
         *        exist in multiple hierarchies, it moves the processes in each 
         *        of those groups. Ensure that the cgroup exists within each of 
         *        the hierarchies whose subsystems you specify here.
         *        e.g. "cpu"
         * @param path is the path to the cgroup within its hierarchy.
         *        e.g. "group-cpu-half"
         * @param pidlist is a space-separated list of PIDs.
         *        e.g. "1234" or "1234 2345" etc.
         */
        std::string cg_classify(
            const std::string& subsys = std::string(""),
            const std::string& path = std::string(""),
            const std::string& pidlist = std::string("")
        );

        /*
         * @param is a comma-separated list of subsystems, or * to launch the 
         *        process in the hierarchies associated with all available 
         *        subsystems. Note that, if cgroups of the same name exist in 
         *        multiple hierarchies, it creates processes in each 
         *        of those groups. Ensure that the cgroup exists within each 
         *        of the hierarchies whose subsystems you specify here.
         *        e.g. "cpu"
         * @param path is the path to the cgroup relative to the hierarchy.
         *        e.g. "group-cpu-half"
         * @param cmd is the command to run.
         *        e.g. "ls"
         * @param opts are any arguments for the command.
         *        e.g. "-lha"
         */
        std::string cg_exec(
            const std::string& subsys = std::string(""),
            const std::string& path = std::string(""),
            const std::string& cmd = std::string(""),
            const std::string& opts = std::string("")
        );

    private:
        /*
         * Copy function of the class
         */
        void do_copy(const CgManager& obj);

        /*
         * Get the pclose return code, which is the sub-process
         * return code.
         */
        std::string get_pclose_rtn_str(const int rtn_pclose);

};

#endif
