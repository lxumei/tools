#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

void sigint_handler(int sig){
    printf("Caught SIGINT\n");
    exit(0);
}

void unix_error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int main(){

    if(signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");

    pause();

    return 0;
}

