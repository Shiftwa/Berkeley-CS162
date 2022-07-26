#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit lim;
    long a = getrlimit(RLIMIT_STACK,&lim);
   
   
 
    printf("stack size: %ld\n", lim.rlim_cur);
     long b = getrlimit(RLIMIT_NPROC,&lim);
    printf("process limit: %ld\n", lim.rlim_cur);
     long c = getrlimit(RLIMIT_NOFILE,&lim);
    printf("max file descriptors: %ld\n", lim.rlim_cur);
    return 0;   
}
