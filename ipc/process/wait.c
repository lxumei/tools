#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){

    pid_t pid = fork();
    if(pid < 0){
        perror("fork failed\n");
        exit(1);
    }
    else if(pid == 0){
        printf("This is child proces, pid = %d.\n", getpid());
        sleep(10);
        while(1){
        }
    }
    else{
        int status;
        pid_t pid2 = fork(); //if there is no child process, wtermsig(status) == 92
        waitpid(pid, &status, WNOHANG);
        if(WIFEXITED(status)){
            printf("Child process exited with code %d.\n", WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("child process terminated abnormally, signal %d.\n", WTERMSIG(status)); 
        }
    }

    return 0;
}

/*
child process terminated abnormally, signal 92.
This is child proces, pid = 121092.
child process terminated abnormally, signal 92.
*/
