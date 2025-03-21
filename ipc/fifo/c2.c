#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define FIFO_FILE "fifo_twoway"

int main(){
    int fd;
    int end_process;
    int stringlen;
    int read_bytes;
    char readbuf[80];
    char end_str[5];

    printf("FIFO_CLIENT:Send messages, infinitely, to end enter \"end\" \n");
    fd = open(FIFO_FILE, O_CREAT|O_RDWR);
    strcpy(end_str, "end");

    while(1){
        printf("Enter string: ");
        if(fgets(readbuf, sizeof(readbuf), stdin)==NULL) //fgets会添加换行符号
            perror("fgets error");
        stringlen = strlen(readbuf);
        readbuf[stringlen-1] = '\0';
        end_process = strcmp(readbuf, end_str);

        if(end_process!=0){
            write(fd, readbuf, strlen(readbuf));
            printf("FIFO_CLINE:Send string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            /*
            read_bytes = read(fd, readbuf, sizeof(readbuf)-1);
            if(read_bytes == -1)
                perror("read error");
            readbuf[read_bytes] = '\0';
            printf("FIFO_CLINE:Receive string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            */
        }
        else{
            write(fd, readbuf, strlen(readbuf));
            printf("FIFO_CLINE:Send string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            close(fd);
            break;
        }
    }
    return 0;
}
