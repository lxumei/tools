#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

int main(){
    pid_t pid;

    if((pid = fork()) == 0){
        pause();
        printf("Control should never reach here!\n");
        exit(0);
    }

    kill(pid, SIGKILL);
    exit(0);
}
