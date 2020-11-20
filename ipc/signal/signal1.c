#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include "csapp.h"
#include<errno.h>
#include<sys/wait.h>

#define MAXBUF 100

void handler1(int sig);
void handler2(int sig);
void handler3(int sig);

int main(){
    int i, n;
    char buf[MAXBUF];

    if(signal(SIGCHLD, handler2) == SIG_ERR)
        unix_error("signal error");

    if(signal(SIGINT, handler3) == SIG_ERR)
        unix_error("signal error");

    for(i = 0; i < 3; i++){
        if(fork() == 0){
            printf("Hello from child %d\n", (int)getpid());
            exit(0);
        }
    }

    if((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read");

    printf("Parent processing input\n");

    exit(0);
}

void handler1(int sig){
    int olderrno = errno;

    if((waitpid(-1, NULL, 0)) < 0)
        sio_error("Waitpid error");

    sio_puts("Handler reaped child\n");
    sleep(1);
    errno = olderrno;
}

void handler2(int sig){
    sio_puts("handler2\n");
    kill(getpid(), SIGINT);
    sio_puts("handler2 end\n");
    return;

    int olderrno = errno;
    while (waitpid(-1, NULL, 0) > 0){
        sio_puts("Handler reaped child\n");
    }
    if(errno != ECHILD)
        unix_error("waitpid error");
    sleep(1);
    errno = olderrno;
}

void handler3(int sig){
    sio_puts("handler3\n");
    kill(getpid(), SIGCHLD);
    sio_puts("handler3 end\n");
    return;
}
