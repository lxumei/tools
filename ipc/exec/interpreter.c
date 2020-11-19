#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t pid = fork();
    if(pid < 0)
        perror("fork failed");
    else if(pid == 0)
        if(execl("/home/lxumei/github/tools/ipc/inter", "inter", "arg1", "arg2", (char *)0) < 0)
            perror("execl error");
    if(waitpid(pid, NULL, 0) < 0)
        perror("waitpid error");
    return 0;
}
