#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void father_to_child(){
    int n;
    int fd[2];
    char line[20];
    pid_t pid;
    
    if(pipe(fd) < 0)
        perror("pipe error");

    pid = fork();
    if(pid < 0)
        perror("fork error");
    else if(pid == 0){
        close(fd[1]);   //close write
        n = read(fd[0], line, 13);
        write(STDOUT_FILENO, line, n);
    }
    else{
        close(fd[0]);
        write(fd[1], "Hello world!\n", 13);
        sleep(1);
        //wait(NULL);
    }
    exit(0);
}

int main(){
    father_to_child();
    return 0;
}
