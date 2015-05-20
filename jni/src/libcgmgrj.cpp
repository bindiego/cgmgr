#include "LibCgmgrJ.h"
#include "cgmgr.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;

/*
 * Class:     LibCgmgrJ
 * Method:    getReturnCode
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_LibCgmgrJ_getReturnCode
  (JNIEnv* env, jobject obj, jstring str)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    // FIXME: this operation could fail in javavm, more actions required later.
    const char* cstr_str = env->GetStringUTFChars(str, 0);
    const string& str_str = string(cstr_str);
    env->ReleaseStringUTFChars(str, cstr_str);

    // call to libcgmgr
    jint rtn = cgm->get_rtn_code(str_str);

    // release CgManager
    delete cgm;

    return rtn;
}

/*
 * Class:     LibCgmgrJ
 * Method:    getReturnOutput
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_getReturnOutput
  (JNIEnv* env, jobject obj, jstring str)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_str = env->GetStringUTFChars(str, 0);
    const string& str_str = string(cstr_str);
    env->ReleaseStringUTFChars(str, cstr_str);

    // call to libcgmgr
    string rtn = cgm->get_rtn_output(str_str);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    ls
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_ls
  (JNIEnv* env, jobject obj, jstring opts)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_opts = env->GetStringUTFChars(opts, 0);
    const string& str_opts = string(cstr_opts);
    env->ReleaseStringUTFChars(opts, cstr_opts);

    // call to libcgmgr
    string rtn = cgm->ls(str_opts);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    which
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_which
  (JNIEnv* env, jobject obj, jstring pg)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_pg = env->GetStringUTFChars(pg, 0);
    const string& str_pg = string(cstr_pg);
    env->ReleaseStringUTFChars(pg, cstr_pg);

    // call to libcgmgr
    string rtn = cgm->which(str_pg);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 *  * Class:     LibCgmgrJ
 *   * Method:    cgList
 *    * Signature: ()Ljava/lang/String;
 *     */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgList
  (JNIEnv* env, jobject obj)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // call to libcgmgr
    string rtn = cgm->cg_list();

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgCreateHierarchy
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgCreateHierarchy
  (JNIEnv* env, jobject obj, jstring subsys, jstring path)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_subsys = env->GetStringUTFChars(subsys, 0);
    const string& str_subsys = string(cstr_subsys);
    env->ReleaseStringUTFChars(subsys, cstr_subsys);

    const char* cstr_path = env->GetStringUTFChars(path, 0);
    const string& str_path = string(cstr_path);
    env->ReleaseStringUTFChars(path, cstr_path);

    // call to libcgmgr
    string rtn = cgm->cg_create_hierarchy(str_subsys, str_path);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgCreateGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgCreateGroup
  (JNIEnv* env, jobject obj, jstring subsys, 
   jstring path, jstring scheduler, jstring admin)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_subsys = env->GetStringUTFChars(subsys, 0);
    const string& str_subsys = string(cstr_subsys);
    env->ReleaseStringUTFChars(subsys, cstr_subsys);

    const char* cstr_path = env->GetStringUTFChars(path, 0);
    const string& str_path = string(cstr_path);
    env->ReleaseStringUTFChars(path, cstr_path);

    const char* cstr_scheduler = env->GetStringUTFChars(scheduler, 0);
    const string& str_scheduler = string(cstr_scheduler);
    env->ReleaseStringUTFChars(scheduler, cstr_scheduler);

    const char* cstr_admin = env->GetStringUTFChars(admin, 0);
    const string& str_admin = string(cstr_admin);
    env->ReleaseStringUTFChars(admin, cstr_admin);

    // call to libcgmgr
    string rtn = cgm->cg_create_group(str_subsys, str_path,
        str_scheduler, str_admin);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgDelGroup
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgDelGroup
  (JNIEnv* env, jobject obj, jstring subsys, jstring path)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_subsys = env->GetStringUTFChars(subsys, 0);
    const string& str_subsys = string(cstr_subsys);
    env->ReleaseStringUTFChars(subsys, cstr_subsys);

    const char* cstr_path = env->GetStringUTFChars(path, 0);
    const string& str_path = string(cstr_path);
    env->ReleaseStringUTFChars(path, cstr_path);

    // call to libcgmgr
    string rtn = cgm->cg_del_group(str_subsys, str_path);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgSetValue
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgSetValue
  (JNIEnv* env, jobject obj, jstring parameter, 
   jstring value, jstring path)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_p = env->GetStringUTFChars(parameter, 0);
    const string& str_p = string(cstr_p);
    env->ReleaseStringUTFChars(parameter, cstr_p);

    const char* cstr_v = env->GetStringUTFChars(value, 0);
    const string& str_v = string(cstr_v);
    env->ReleaseStringUTFChars(value, cstr_v);

    const char* cstr_path = env->GetStringUTFChars(path, 0);
    const string& str_path = string(cstr_path);
    env->ReleaseStringUTFChars(path, cstr_path);

    // call to libcgmgr
    string rtn = cgm->cg_set_value(str_p, str_v, str_path);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgSetCopy
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgSetCopy
  (JNIEnv* env, jobject obj, jstring fg, jstring tg)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_fg = env->GetStringUTFChars(fg, 0);
    const string& str_fg = string(cstr_fg);
    env->ReleaseStringUTFChars(fg, cstr_fg);

    const char* cstr_tg = env->GetStringUTFChars(tg, 0);
    const string& str_tg = string(cstr_tg);
    env->ReleaseStringUTFChars(tg, cstr_tg);

    // call to libcgmgr
    string rtn = cgm->cg_set_copy(str_fg, str_tg);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgClassify
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgClassify
  (JNIEnv* env, jobject obj, jstring subsys, jstring path, 
   jstring pidlist)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_subsys = env->GetStringUTFChars(subsys, 0);
    const string& str_subsys = string(cstr_subsys);
    env->ReleaseStringUTFChars(subsys, cstr_subsys);

    const char* cstr_path = env->GetStringUTFChars(path, 0);
    const string& str_path = string(cstr_path);
    env->ReleaseStringUTFChars(path, cstr_path);

    const char* cstr_pidlist = env->GetStringUTFChars(pidlist, 0);
    const string& str_pidlist = string(cstr_pidlist);
    env->ReleaseStringUTFChars(pidlist, cstr_pidlist);

    // call to libcgmgr
    string rtn = cgm->cg_classify(str_subsys, str_path, str_pidlist);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

/*
 * Class:     LibCgmgrJ
 * Method:    cgExec
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_LibCgmgrJ_cgExec
  (JNIEnv* env, jobject obj, jstring subsys, jstring path, 
   jstring cmd, jstring opts)
{
    // create the CgManager
    CgManager* cgm = new CgManager();

    // handle passed in parameters
    const char* cstr_subsys = env->GetStringUTFChars(subsys, 0);
    const string& str_subsys = string(cstr_subsys);
    env->ReleaseStringUTFChars(subsys, cstr_subsys);

    const char* cstr_path = env->GetStringUTFChars(path, 0);
    const string& str_path = string(cstr_path);
    env->ReleaseStringUTFChars(path, cstr_path);

    const char* cstr_cmd = env->GetStringUTFChars(cmd, 0);
    const string& str_cmd = string(cstr_cmd);
    env->ReleaseStringUTFChars(cmd, cstr_cmd);

    const char* cstr_opts = env->GetStringUTFChars(opts, 0);
    const string& str_opts = string(cstr_opts);
    env->ReleaseStringUTFChars(opts, cstr_opts);

    // call to libcgmgr
    string rtn = cgm->cg_exec(str_subsys, str_path, 
        str_cmd, str_opts);

    // release CgManager
    delete cgm;

    // return jstring
    return env->NewStringUTF(rtn.c_str());
}

#ifdef __cplusplus
}
#endif
