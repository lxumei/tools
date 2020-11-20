#ifndef _CSAPP_H_
#define _CSAPP_H_

#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>

void unix_error(char *msg);
ssize_t sio_puts(char s[]);
void sio_error(char s[]);
ssize_t sio_putl(long v);

static void sio_reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void sio_ltoa(long v, char s[], int b)
{
    int c, i = 0;

    do {
        s[i++] = ((c = (v % b)) < 10)  ?  c + '0' : c - 10 + 'a';
    } while ((v /= b) > 0);
    s[i] = '\0';
    sio_reverse(s);
}

void unix_error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

ssize_t sio_puts(char s[]){
    return write(STDOUT_FILENO, s, strlen(s));
}

void sio_error(char s[]){
    sio_puts(s);
    _exit(1);
}

ssize_t sio_putl(long v){
    char s[128];
    sio_ltoa(v, s, 10);
    return sio_puts(s);
}

#endif
