#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

#define MAXLINE 13

static void sig_pipe(int);

int main(){
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAXLINE+1];
    
    if(signal(SIGPIPE, sig_pipe) == SIG_ERR){
        printf("signal error\n");
        exit(0);
    }

    if(pipe(fd1) < 0 || pipe(fd2) < 0){
        printf("pipe error\n");
        exit(0);
    }

    if((pid=fork()) < 0){
        printf("fork error\n");
        exit(0);
    }
    else if(pid > 0){
        close(fd1[0]);  //close read
        close(fd2[1]);  //close write
        while(fgets(line, MAXLINE, stdin)!=NULL){
            n = strlen(line);
            if(write(fd1[1], line, n) != n){
                printf("write error\n");
                exit(0);
            }
            if( (n = read(fd2[0], line, MAXLINE)) < 0){
                printf("read from pipe error\n");
                exit(0);
            }
            if( n == 0){
                printf("Child Process close pipe\n");
                break;
            }
            line[n] = 0;
            if(fputs(line, stdout) == EOF){
                printf("fputs error\n");
                exit(0);
            }
        }
        if(ferror(stdin)){
            printf("fgets error on stdin\n");
            exit(0);
        }
    }
    else{
        close(fd1[1]);
        close(fd2[0]);
        if(fd1[0] != STDIN_FILENO){
            if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO){
                printf("dup2 error to stdin\n");
                exit(0);
            }
            close(fd1[0]);
        }

        if(fd2[1] != STDOUT_FILENO){
            if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO){
                printf("dup2 error to stdout\n");
                exit(0);
            }
            close(fd2[1]);
        }

        if(execl("./add2", "add2", (char *) 0) < 0){
            printf("execl error\n");
            exit(0);
        }
    }
    exit(0);
}

static void sig_pipe(int signo){
    printf("SIGPIPE caught\n");
    exit(1);
}
