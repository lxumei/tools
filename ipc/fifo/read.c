#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
    char readbuf[80];
    memset(readbuf, 0, sizeof(readbuf));
    int fd = open("test", O_RDONLY);
    if(fd < 0)
        perror("open error");
    int read_bytes = read(fd, readbuf, 8);
    if(read_bytes == -1)
        perror("read error");
    readbuf[read_bytes] = '\0';
    printf("string = %s\nlength = %d\n", readbuf, strlen(readbuf));

    
    //char testbuf[] = {'1', '2', '\0', '4'};
    char *testbuf = "hello";
    printf("string = %s, length(sizeof) = %d, length(strlen) = %d", testbuf, sizeof(testbuf), strlen(testbuf)); 

    return 0;
}
