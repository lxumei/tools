#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 10
#define SHM_KEY 0x1234

struct shmseg{
    int cnt;
    int complete;
    char buf[BUF_SIZE];
};

int fill_buffer(char *bufptr, int size);

int main(int argc, char *argv[]){
    int shmid, numtimes;
    struct shmseg *shmp;
    char *bufptr;
    int spaceavaiable;
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
    if(shmid == -1){
        perror("shared memory error");
        return 1;
    }

    shmp = shmat(shmid, NULL, 0);
    if(shmp == (void *) -1){
        perror("share memory attach error");
        return 1;
    }
    
    bufptr = shmp->buf;
    spaceavaiable = BUF_SIZE;
    
    for(numtimes = 0; numtimes < 5; numtimes++){
        shmp->cnt = fill_buffer(bufptr, spaceavaiable);
        shmp->complete = 0;
        printf("Writing Process: Shared Memory Write, Wrote %d bytes\n", shmp->cnt);
        bufptr = shmp->buf;
        spaceavaiable = BUF_SIZE;
        sleep(3);
    }

    printf("Writing Process: Wrote %d times\n", numtimes);
    shmp->complete = 1;

    if(shmdt(shmp) == -1){
        perror("shmdt");
        return 1;
    }

    if(shmctl(shmid, IPC_RMID, 0) == 1){
        perror("shmctl");
        return 1;
    }

    printf("Writing Peocess: Complete\n");
    return 0;
}

int fill_buffer(char * bufptr, int size) {
   static char ch = 'A';
   int filled_count;

   //printf("size is %d\n", size);
   memset(bufptr, ch, size - 1);
   bufptr[size-1] = '\0';
   if (ch > 122)
   ch = 65;
   if ( (ch >= 65) && (ch <= 122) ) {
      if ( (ch >= 91) && (ch <= 96) ) {
         ch = 65;
      }
   }
   filled_count = strlen(bufptr);

   //printf("buffer count is: %d\n", filled_count);
   //printf("buffer filled is:%s\n", bufptr);
   ch++;
   return filled_count;
}

