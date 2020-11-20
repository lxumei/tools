#include "csapp.h"

volatile sig_atomic_t pid;

void sigchld_handler(int s){
    int olderrno = errno;
    pid = waitpid(-1, NULL, 0);
    errno = olderrno;
}

void sigint_handler(int s){
}

int main(int argc, char **argv){
    sigset_t mask, prev;

    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, sigint_handler);
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);

    while(1){
        sigprocmask(SIG_BLOCK, &mask, &prev);
        if(fork() == 0)
            exit(0);

        pid = 0;
        while(!pid)
            sigsuspend(&prev);

        sigprocmask(SIG_SETMASK, &prev, NULL);

        printf(".");
    }

    exit(0);
}
