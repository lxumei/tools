#include "csapp.h"

void handler(int sig){
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    pid_t pid;

    sigfillset(&mask_all);
    while((pid = waitpid(-1, NULL, 0)) > 0){
        sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob(pid);
        sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }

    if(errno != ECHILD)
        unix_error("waitpid error");
}

int main(int argc, char **argv){
    int pid;
    sigset_t mask_all, mask_one, prev_one;

    sigfillset(&mask_all);
    sigemptyset(&mask_one);
    sigaddset(&mask_one, SIGCHLD);
    signal(SIGCHLD, handler);
    initjobs();

    while(1){
        sigprocmask(SIG_BLOCK, &mask_one, &prev_one);
        if((pid = fork()) == 0){
            sigprocmask(SIG_SETMASK, &prev_one, NULL);
            execve("/bin/data", argv, NULL);
        }
        sigprocmask(SIG_BLOCK, &mask_all, NULL);
        addjob(pid);
        sigprocmask(SIG_SETMASK, &prev_one, NULL);
    }
    exit(0);
}
