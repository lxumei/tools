#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 13

int main(int argc, char* argv[]){
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;
    
    if(argc != 2){
        perror("usage: a.out <pathname>");
        exit(0);
    }
    if( (fp=fopen(argv[1], "r")) == NULL )
        perror("can't open file");
    if(pipe(fd) < 0)
        perror("pipe error");

    if( (pid = fork()) < 0)
        perror("fork error");

    else if(pid == 0){
       printf("Child Process!\n");
       close(fd[1]);
       if(fd[0] != STDIN_FILENO){
            if( dup2(fd[0], STDIN_FILENO) != STDIN_FILENO )
                perror("dup error to stdin");
            close(fd[0]);
        }

        pager = DEF_PAGER;
       if((argv0 = strrchr(pager, '/'))!=NULL)
           argv0++;
       else
           argv0 = pager;
       printf("pager = %s, argv0 = %s\n", pager, argv0);
       if(execl(pager, argv0, "-d", "pipe.c", (char *) 0) < 0)
           perror("execl error for pager");
    }

    else{
        printf("Parent process!\n");
        close(fd[0]);
        while(fgets(line, MAXLINE, fp) !=NULL){
            n = strlen(line);
            if(write(fd[1], line, n) != n)
                perror("write error to pipe");
        }
        if(ferror(fp))
            perror("fgets error");
        close(fd[1]);
        if(waitpid(pid, NULL, 0) < 0)
            perror("waitpid error");
        exit(0);
    }
    return 0;
}
