#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

char *env_init[] = {"USER = unknonw", "PATH = /tmp:.", NULL};

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0)
        perror("fork failed\n");
    else if(pid == 0){
        if(execle("/home/lxumei/github/tools/ipc/echoall", "echoall", "arg1", "arg2", (char *)0, env_init) < 0)
            perror("execle error\n");
        exit(0);
    }

    if(waitpid(pid, NULL, 0) < 0)
        printf("wait error\n");

    printf("before second fork\n");
    pid = fork();
    if(pid < 0)
        perror("fork failed\n");
    else if(pid == 0){
        if(execlp("echoall", "eachoall", "only 1 arg", (char *)0) < 0)
            perror("execlp error");
    }
    return 0;
}

/* echoall.c

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int i;
    char **ptr;
    extern char **environ;

    for( i=0; i<argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);

    for(ptr = environ; *ptr !=0; ptr++)
        printf("%s\n", *ptr);

    exit(0);
}

*/
