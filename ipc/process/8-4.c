#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>

void pr_exit(int status){
    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination,  signal number = %d%s\n", WTERMSIG(status),
        #ifdef WCOREDUMP
            WCOREDUMP(status) ? "(core file generated)" : "");
        #else
            "");
        #endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(){

    pid_t pid;
    int status;
    pid = fork();

    if(pid < 0)
        perror("fork failed\n");
    else if(pid == 0)
        exit(7);
    if(wait(&status) != pid)
        perror("wait error\n");
    pr_exit(status);

    pid = fork();
    if(pid < 0)
        perror("fork failed\n");
    else if(pid == 0)
        abort();
    if(wait(&status) != pid)
        perror("wait error\n");
    pr_exit(status);

    pid = fork();
    if(pid < 0)
        perror("fork failed\n");
    else if(pid == 0)
        status /= 0;
    if(wait(&status) != pid)
        perror("wait error\n");
    pr_exit(status);

    exit(0);
}

