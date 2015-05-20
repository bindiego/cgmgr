#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include <string>
#include <iostream>
#include <cgmgr.h>

/*
 * @Author: Bin Wu
 * @Date: 21/Sep/2013
 */

using namespace std;

void cpu_intensive() {
    double start, end;
    double run_time;

    start = omp_get_wtime();
    int num = 1, primes = 0;

    int limit = 200000;

#pragma omp parallel for schedule(dynamic) reduction(+ : primes)
    for (num = 1; num <= limit; num++) {
        int i = 2;

        while(i <= num) {
            if (num % i == 0)
                break;
            i++;
        }

        if (i == num) {
            printf("%d\t",num);
            primes++;
        }
    }

    end = omp_get_wtime();
    run_time = end - start;

    printf("\n\nThis machine calculated all %d prime numbers under %d in %g seconds.\n\n",primes,limit,run_time);
}

void cgm_tests(void) 
{
    // create the CSI CgManager
    CgManager* cgm = new CgManager();

    string rtn_ls1 = cgm->ls(string("lha"));
    //cout << rtn_ls1;
    cout << "Return Code: " << cgm->get_rtn_code(rtn_ls1) << endl;
    cout << "Return Output: " << endl << cgm->get_rtn_output(rtn_ls1) << endl;

    string rtn_ls2 = cgm->ls(string("e"));
    //cout << rtn_ls2;
    cout << "Return Code: " << cgm->get_rtn_code(rtn_ls2) << endl;
    cout << "Return Output: " << endl << cgm->get_rtn_output(rtn_ls2) << endl;

    string str_rtn = cgm->which(string("ls"));
    //cout << str_rtn;
    cout << "Return Code: " << cgm->get_rtn_code(str_rtn) << endl;
    cout << "Return Output: " << endl << cgm->get_rtn_output(str_rtn) << endl;

    str_rtn = cgm->cg_list();
    //cout << str_rtn;
    cout << "Return Code: " << cgm->get_rtn_code(str_rtn) << endl;
    cout << "Return Output: " << endl << cgm->get_rtn_output(str_rtn) << endl;

    /*
    string cg_rtn = cgm->cg_create_hierarchy("abc", "/home/binw/abc");
    cout << "Return Code: " << cgm->get_rtn_code(cg_rtn) << endl;
    cout << "Return Output: " << endl << cgm->get_rtn_output(cg_rtn) << endl;
    */

    // release CgManager created
    delete cgm;
}

int main(int argc, char* argv[]) {
    //cpu_intensive();

    //system("ls -lh");
    cgm_tests();

    return 0;
}

// EOF

