#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

unsigned int snooze(unsigned int secs){
    int res = sleep(secs);
    printf("Slept for %d of %d secs.\n", secs - res, secs);
    return res;
}

void sigint_handler(int sig){
   return; 
}

void unix_error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/* 只要休眠进程收到一个未被忽略的信号，sleep函数就会提前返回 */
int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <sec>\n", argv[0]);
        return 0;
    }

    if(signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");

    snooze(atoi(argv[1]));

    return 0;
}

