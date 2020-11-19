#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<assert.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

void env(){
    printf("HOME path; %s\n", getenv("HOME"));
}

/*Without fflush(stdout), we will get two  ***begin...*** in the output.
  We can also using printf("begin...\n"), in this case, ***begin...*** appears once.
*/
void ffork(){
    printf("begin...");
    fflush(stdout);
    pid_t pid = fork();
    if(pid == 0){
        printf("this is child process\n");
    }
    else{
        printf("this is father process\n");
    }
}

void get_p_ppid(){
    printf("\n---get_p_ppid begin--\n");
    pid_t pid = fork();
    if(pid < 0){
        printf("Error in fork()\n");
    }
    else if(pid == 0){
        printf("I am child process, my pid is %d, my parent is %d.\n", getpid(), getppid());
    }
    else if(pid > 0){
        sleep(1);
        printf("I am parent process, my pid is %d, may parent is %d.\n", getpid(), getppid());
        printf("---get_p_ppid end--\n");
    }
}

/*Create n ***child*** process by fork().
  To avoid generate child process by created child process, ***break*** is needed.
  2^n-1 child process will be created without the break, because the forked  process can still generate child process.
*/
void create_n_child_process(){
    printf("\n---create_n_child_process---\n");
    int i, n = 2;
    for(i = 0; i<n; i++){
        pid_t pid = fork();
        if(pid < 0){
            printf("Error in fork()\n");
        }
        else if(pid == 0){
            printf("This is child process, i = %d, pid = %d, ppid = %d.\n", i, getpid(), getppid());
            break;
        }
        else{
            printf("This is parent process, i = %d, pid = %d, ppid = %d.\n", i, getpid(), getppid());
        }
    }

    if(i < n){
        printf("[+] I am child process, i = %d, pid = %d, ppid = %d.\n", i, getpid(), getppid());
    }
    else{
        printf("[+] I am parent process, i = %d, pid = %d, ppid = %d.\n", i, getpid(), getppid());
    }
}

/* Is child and parent processes share global and local variables?
   Child and parent proceses do not share global and local variables.
   They also do not share data in heap.
   But they ***share*** the ***file descriptor***.
*/
int g1 = 31;
void local_global_variable_change(){
    printf("\n---local and variable change in child and parent process---\n");

    int l1 = 45;
    int *a = (int *)malloc(sizeof(int));
    char str[] = {'h','e','l', 'l','o','w','\n'};
    int fd = open("a.txt", O_CREAT|O_RDWR, 0664);
    assert(fd!=-1);
    *a = 10;
    printf("global variable g1 = %d, local variable l1 = %d, *a = %d\n", g1, l1, *a); 

    pid_t pid = fork();
    if(pid < 0){
        printf("Error in fork()\n");
    }
    else if(pid == 0){
        g1 += 5;
        l1 += 5;
        *a += 5;
        write(fd, str, 7);
        printf("%d\n",  lseek(fd, 0, SEEK_CUR));
        printf("This is child process, g1 = %d, l1 = %d, *a = %d\n", g1, l1, *a);
    }
    else{
        sleep(1);
        g1 += 5;
        l1 += 5;
        *a += 5;
        char buf[10];
        memset(buf, 0, 10);
        printf("%d\n",  lseek(fd, 0, SEEK_CUR));
        lseek(fd, 0, SEEK_SET);
        read(fd, (char*)buf, sizeof(buf));
        //buf[sizeof(buf)-1] = '\0';
        printf("This is parent process, g1 = %d, l1 = %d, *a = %d\n", g1, l1, *a);
        printf("%s",buf);
        close(fd);
    }
}


/* Two process open the same file */
void two_process_open_file(){

    int fd = open("a.txt", O_RDWR|O_CREAT, 0664);
    pid_t pid = fork();
    if(pid < 0){
        perror("fork failed\n");
        exit(1);
    }
    else if(pid == 0){
        printf("This is child process.\n");
        char str[] = {'h','e','l', 'l','o','w','\n'};
        write(fd, str, 7);
        printf("%d\n",  lseek(fd, 0, SEEK_CUR));
        close(fd);
        fd = open("a.txt", O_RDWR|O_CREAT, 0664);
        printf("%d\n",  lseek(fd, 0, SEEK_CUR));
    }
    else{
        sleep(1);
        printf("This is parent process.\n");
        printf("%d\n",  lseek(fd, 0, SEEK_CUR));
        printf("%d\n",  fd);
        char str1[] = {'h','e','l', 'l','o','1','\n'};
        int ret = write(fd, str1, 7);
        printf("%d\n", ret);
    }
}

int main(){
    //get_p_ppid();
    //create_n_child_process();
    //local_global_variable_change();
    two_process_open_file();
    return 0;
}
