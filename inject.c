#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<dlfcn.h>
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/user.h>

void usage(char *binary){
    printf("usage: %s -p targetpid -l targetlibrary", binary);
}


long get_libc_addr(pid_t pid){
    char *maps_path = (char *)malloc(20);
    sprintf(maps_path, "/proc/%d/maps", pid);

    FILE *fp = fopen(maps_path, "r");
    if(fp == 0){
        fprintf(stderr, "open %s falid", maps_path);
        exit(1);
    }

    char *line = 0, *off;
    size_t len = 0;
    long ret = 0;
    while((ret = getline(&line, &len, fp)) != -1){
        off = strstr(line, "libc-");
        if(off){
            ret = strtoul(line, NULL, 16);
            break;
        }
    }

    if(line) free(line);

    fclose(fp);
    return ret;
}


long get_func_addr(char *func){
   void *self = dlopen("libc.so.6", RTLD_LAZY);
   if(self == 0){
       printf("dlopen libc.so.6 failed\n");
       exit(1);
   }

   void *funcAddr = dlsym(self, func);
   if(funcAddr == 0){
       printf("dlsym %s failed\n", func);
       exit(1);
    }
   
    return (long)funcAddr;
}


void ptrace_attach(pid_t target)
{
	int waitpidstatus;

	if(ptrace(PTRACE_ATTACH, target, NULL, NULL) == -1)
	{
		fprintf(stderr, "ptrace(PTRACE_ATTACH) failed\n");
		exit(1);
	}

	if(waitpid(target, &waitpidstatus, WUNTRACED) != target)
	{
		fprintf(stderr, "waitpid(%d) failed\n", target);
		exit(1);
	}
}


void ptrace_getregs(pid_t target, struct user_regs_struct * regs)
{
	if(ptrace(PTRACE_GETREGS, target, NULL, regs) == -1)
	{
		fprintf(stderr, "ptrace(PTRACE_GETREGS) failed\n");
		exit(1);
	}
}

void ptrace_setregs(pid_t target, struct user_regs_struct* regs)
{
	if(ptrace(PTRACE_SETREGS, target, NULL, regs) == -1)
	{
		fprintf(stderr, "ptrace(PTRACE_SETREGS) failed\n");
		exit(1);
	}
}

void ptrace_read(int pid, unsigned long addr, void *vptr, int len)
{
	int bytesRead = 0;
	int i = 0;
	long word = 0;
	long *ptr = (long *) vptr;

	while (bytesRead < len)
	{
		word = ptrace(PTRACE_PEEKTEXT, pid, addr + bytesRead, NULL);
		if(word == -1)
		{
			fprintf(stderr, "ptrace(PTRACE_PEEKTEXT) failed\n");
			exit(1);
		}
		bytesRead += sizeof(word);
		ptr[i++] = word;
	}
}

void ptrace_write(int pid, unsigned long addr, void *vptr, int len)
{
	int byteCount = 0;
	long word = 0;

	while (byteCount < len)
	{
		memcpy(&word, vptr + byteCount, sizeof(word));
		word = ptrace(PTRACE_POKETEXT, pid, addr + byteCount, word);
		if(word == -1)
		{
			fprintf(stderr, "ptrace(PTRACE_POKETEXT) failed\n");
			exit(1);
		}
		byteCount += sizeof(word);
	}
}

void ptrace_detach(pid_t target)
{
	if(ptrace(PTRACE_DETACH, target, NULL, NULL) == -1)
	{
		fprintf(stderr, "ptrace(PTRACE_DETACH) failed\n");
		exit(1);
	}
}

void ptrace_cont(pid_t target)
{
    struct timespec* sleeptime = malloc(sizeof(struct timespec));

    sleeptime->tv_sec = 0;
    sleeptime->tv_nsec = 5000000;

    if(ptrace(PTRACE_CONT, target, NULL, NULL) == -1)
    {
        fprintf(stderr, "ptrace(PTRACE_CONT) failed\n");
        exit(1);
    }

    nanosleep(sleeptime, NULL);

    // make sure the target process received SIGTRAP after stopping.
    //checktargetsig(target);
}

void restoreStateAndDetach(pid_t target, unsigned long addr, void* backup, int datasize, struct user_regs_struct oldregs)
{
    int status;
    waitpid(target, &status, 0);
	ptrace_write(target, addr, backup, datasize);
	ptrace_setregs(target, &oldregs);
	ptrace_detach(target);
}

int main(int argc, char **argv){
    int opt;
    char *libpath;
    pid_t targetpid;

    while((opt = getopt(argc, argv, "+p:+l:")) > 0){
        switch (opt){
            case 'p':
                targetpid = atoi(optarg);
                break;
            case 'l':
                libpath = optarg;
                break;
        }
    }

    if(optind != argc){
        usage(argv[0]);
        exit(1);
    }

    char tmp[20];
    sprintf(tmp, "/proc/%d", targetpid);
    if(access(tmp, 0) != 0){
        printf("targetpid \"%d\" doesn't exist\n", targetpid);
        exit(1);
    }

    FILE *fp;
    if((fp = fopen(libpath, "r")) == 0){
        printf("library file \"%s\" doesn't exist\n", libpath);
        exit(1);
    }
    fclose(fp);
    libpath = realpath(libpath, NULL);
    printf("injected shared library %s\n", libpath);
    int libpathLength = strlen(libpath) + 1;

    pid_t mypid = getpid();
    long libAddr      = get_libc_addr(mypid);
    long dlopenAddr   = get_func_addr("__libc_dlopen_mode");
    long dlopenOffset = dlopenAddr - libAddr;

    long targetlibAddr    = get_libc_addr(targetpid);
    long targetdlopenAddr = targetlibAddr + dlopenOffset;

    printf("libcAddr  = %p\n", libAddr);
    printf("targetlibcAddr  = %p\n", targetlibAddr);

    struct user_regs_struct oldregs, regs;
    memset(&oldregs, 0, sizeof(struct user_regs_struct));
    memset(&regs, 0, sizeof(struct user_regs_struct));

    ptrace_attach(targetpid);

    ptrace_getregs(targetpid, &oldregs);
    memcpy(&regs, &oldregs, sizeof(struct user_regs_struct));
    unsigned long new_rsp   = regs.rsp | 0x8;
    unsigned long old_rbp   = regs.rbp;
    unsigned long start     = new_rsp - 64;
    unsigned long arg1_addr = new_rsp + 16;
    printf("new rsp = %p\n", new_rsp);

    char *old_content = malloc(256); 
    ptrace_read(targetpid, start, old_content, 256); 

    printf("writing lib name to %p\n", arg1_addr);
    ptrace_write(targetpid, arg1_addr, libpath, libpathLength);
    ptrace_write(targetpid, new_rsp, "00000000", 8);
    regs.rsp = new_rsp;
    regs.rip = targetdlopenAddr;
    printf("dlopen: %p\n", targetdlopenAddr);
    //regs.rip = 0x31313131;
    regs.rdi = arg1_addr;
    regs.rsi = RTLD_LAZY;

    ptrace_setregs(targetpid, &regs);
    ptrace_cont(targetpid);
    restoreStateAndDetach(targetpid, start, old_content, 256, oldregs);

    return 0;
}
