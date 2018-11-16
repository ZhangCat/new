
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include "dumpinfo.h"

static void dump()
{
    void *buffer[100]={0};
    size_t size;
    char **strings=NULL;
    size_t i=0;

    size=backtrace(buffer,100);
    strings=backtrace_symbols(buffer,size);

    if(!strings)
    {
        printf("[backtrace_symbols]0\n");
        exit(EXIT_FAILURE);
    }

    printf("[backtrace_symbols]size:%zd\n",size);

    for(i=0;i<size;i++)
        printf("[*%ld*]%s\n",i+1,strings[i]);

    free(strings);
    strings=NULL;
    exit(0);
}

void GetDumpInfo()
{
    if(signal(SIGSEGV,(__sighandler_t)dump)==SIG_ERR)
    {
        printf("[signal dump]error\n");
        return;
    }
    else
    {
        printf("[signal dump]ok\n");
    }

    int pid=getpid();
    char cmdBuf[256]={0x00};
    sprintf(cmdBuf,"cat /proc/%d/maps > ./%d.mps",pid,pid);
    system(cmdBuf);
    printf("[save maps file]%d.mps\n",pid);
}