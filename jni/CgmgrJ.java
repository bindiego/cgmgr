public class CgmgrJ {
    public static void main(String[] args) {
        LibCgmgrJ libcgmgrj = new LibCgmgrJ();

        String rtn = libcgmgrj.ls("lha");
        System.out.println("Return Code: " + libcgmgrj.getReturnCode(rtn));
        System.out.println("Output:\n" + libcgmgrj.getReturnOutput(rtn));

        rtn = libcgmgrj.ls("e");
        System.out.println("Return Code: " + libcgmgrj.getReturnCode(rtn));
        System.out.println("Output:\n" + libcgmgrj.getReturnOutput(rtn));

        rtn = libcgmgrj.which("ls");
        System.out.println("Return Code: " + libcgmgrj.getReturnCode(rtn));
        System.out.println("Output:\n" + libcgmgrj.getReturnOutput(rtn));

        rtn = libcgmgrj.cgList();
        System.out.println("Return Code: " + libcgmgrj.getReturnCode(rtn));
        System.out.println("Output:\n" + libcgmgrj.getReturnOutput(rtn));
    }
}
