#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAXLINE 13
#define PAGER "${PAGER:-more}"

int main(int argc, char *argv[]){
    char line[MAXLINE];
    FILE *fpin, *fpout;
    if(argc != 2){
        printf("usage: ./a.out <pathname>\n");
        exit(0);
    }

    if((fpin = fopen(argv[1], "r")) == NULL){
        printf("can not open %s\n", argv[1]);
        exit(0);
    }

    if((fpout = popen(PAGER, "w")) == NULL){//这里通过popen创建了一个子进程
        printf("popen error\n");
        exit(0);
    }

    while(fgets(line, MAXLINE, fpin) != NULL){
        if(fputs(line, fpout) == EOF){
            printf("fputs error to pipe\n");
            exit(0);
        }
    }

    if(ferror(fpin)){
        printf("fgets error\n");
        exit(0);
    }

    if(pclose(fpout) == -1){
        printf("pclose error\n");
        exit(0);
    }

    exit(0);
}
