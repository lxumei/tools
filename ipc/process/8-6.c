#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
//竞争条件
static void charatatime(char *);

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0)
        perror("fork failed\n");
    else if(pid == 0)
        charatatime("output from child\n");
    else
        charatatime("output from parent\n");
    return 0;
}
static void charatatime(char *str){
    char *ptr;
    int c;
    setbuf(stdout, NULL);
    for(ptr = str; (c = *ptr++)!=0;)
        putc(c, stdout);
}
