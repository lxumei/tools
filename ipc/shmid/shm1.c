#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

#define ARRAR_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600

char array[ARRAR_SIZE];

int main(void){
    int shmid;
    char *ptr, *shmpter;

    printf("array[] from %p to %p\n", (void *)&array[0], (void *)&array[ARRAR_SIZE]);
    printf("stack around %p\n", (void *)&shmid);

    if((ptr = malloc(MALLOC_SIZE)) == NULL){
        printf("malloc error\n");
        exit(0);
    }
    printf("malloced from %p to %p\n", (void *)ptr, (void *)ptr+MALLOC_SIZE);

    if((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0){
        printf("shmget error\n");
        exit(0);
    }
    if((shmpter = shmat(shmid, 0, 0)) == (void *)-1){
        printf("shmat error\n");
        exit(0);
    }
    printf("shared memory attached from %p to %p\n", (void *)shmpter, (void *)shmpter + SHM_SIZE);

    if(shmctl(shmid, IPC_RMID, 0) < 0){
        printf("shmctl error\n");
        exit(0);
    }

    exit(0);
}

/*
array[] from 0x5589bda88040 to 0x5589bda91c80
stack around 0x7ffee130c884
malloced from 0x5589be3ca670 to 0x5589be3e2d10
shared memory attached from 0x7f0f17c89000 to 0x7f0f17ca16a0
*/
