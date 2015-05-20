public class LibCgmgrJ {
    public LibCgmgrJ() {}

    static {
        System.loadLibrary("cgmgrj");
    }

    /* utilities */
    public native int getReturnCode(String str);
    public native String getReturnOutput(String str);

    /* system functions */
    public native String ls(final String opts);
    public native String which(final String pg);

    /* cgroup calls */
    public native String cgList();
    public native String cgCreateHierarchy(
        final String subsys, final String path);
    public native String cgCreateGroup(
        final String subsys, final String path,
        final String scheduler, final String admin);
    public native String cgDelGroup(
        final String subsys, final String path);
    public native String cgSetValue(
        final String parameter, final String value,
        final String path);
    public native String cgSetCopy(
        final String fromGroup, final String toGroup);
    public native String cgClassify(
        final String subsys, final String path, final String pidlist);
    public native String cgExec(
        final String subsys, final String path,
        final String cmd, final String opts);
}

