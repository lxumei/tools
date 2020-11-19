#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define FIFO_FILE "MYFIFO"

int main(){
    int fd;
    int end_process;
    int stringlen;
    char readbuf[80];
    char end_str[5];

    printf("FIFLO_CLINET: Send message, infinitely, to end enter \"end\" \n");
    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
    strcpy(end_str, "end");

    while(1){
        printf("Enter string: ");
        if(fgets(readbuf, sizeof(readbuf), stdin) == NULL)
            perror("fgets error");
        stringlen = strlen(readbuf);
        readbuf[stringlen-1] = '\0';
        end_process = strcmp(readbuf, end_str);

        if(end_process != 0){
            write(fd, readbuf, strlen(readbuf));
            printf("Send string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
        }
        else{
            write(fd, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            close(fd);
            break;
        }
    }

    return 0;
}
        
