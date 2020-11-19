#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int globvar = 6;

int main(){
    int var;
    pid_t pid;
    var = 88;
    printf("before vfork\n");
    pid = vfork();
    if(pid < 0){
        perror("fork failed\n");
    }
    else if(pid == 0){
        //run in the parent's address space before exec or exit
        globvar++;
        var++;
        _exit(0); // not exit(0);
    }

    printf("pid = %d, globvar = %d, var = %d\n", getpid(), globvar, var);
    return 0;
}


