#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h>

#define MAXLINE 1000
#define MAXARGS 100

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void unix_error(char *msg);

int main(){
    char cmdline[MAXLINE];
    
    while(1){
        printf("> ");
        fgets(cmdline, MAXLINE, stdin);
        if(feof(stdin))
            exit(0);
        
        eval(cmdline);
    }
}

void eval(char *cmdline){
    char *argv[MAXARGS];    /* Argument list execve() */
    char buf[MAXLINE];      /* Holds modified command line */
    int bg;                 /* Should the job run in bg or fg */
    pid_t pid;

    /* copy cmdline to buf */
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if(argv[0] == NULL)
        return;             /* Ignore empty lines */

    if(!builtin_command(argv)){
        if((pid = fork()) == 0){
            if(execve(argv[0], argv, NULL) < 0){
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        if(!bg){
            int status;
            if(waitpid(pid, &status, 0)<0)
                unix_error("waitfg: waitpid error");
        }
        else
            printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv){
    if(!strcmp(argv[0], "quit"))
        exit(0);
    if(!strcmp(argv[0], "&"))
        return 1;

    return 0;
}

int parseline(char *buf, char **argv){
    char *delim;        /* Points to first space delimiter */
    int argc;           /* Number of args */
    int bg;             /* Background job? */

    buf[strlen(buf)-1] = ' ';   /* Replace trailing '\n' with space */
    while(*buf && (*buf == ' '))    /*Ingore leading spaces */
        buf++;
    
    argc = 0;
    // The strchr() function returns a pointer to the first occurrence of the character c in the string s.
    while(delim = strchr(buf, ' ')){
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while(*buf && (*buf == ' '))    /* Ingore leading spaces */
            buf++;
    }

    argv[argc] = NULL;

    if(argc == 0)
        return 1;

    if((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}

void unix_error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
