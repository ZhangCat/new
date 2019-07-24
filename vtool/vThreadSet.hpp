#ifndef V_THREADSET_HPP
#define V_THREADSET_HPP

#include <stdio.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sched.h>

static void vGetThreadCpu() {
    cpu_set_t get;
    CPU_ZERO(&get);
    if(sched_getaffinity(0,sizeof(get),&get)==-1) {
        printf("[%s]sched_getaffinity false\n",__FUNCTION__);
        return;
    }

    int cpu_num=sysconf(_SC_NPROCESSORS_CONF);
    for(int i=0;i<cpu_num;i++) {
        if(CPU_ISSET(i,&get)) {
            printf("[%s]sched_getaffinity true:cpu_num=%d cpu_which=%d\n",__FUNCTION__,cpu_num,i);
        }
    }
 }

static void vSetThreadCpu(int cpu_which) {
    int cpu_num=sysconf(_SC_NPROCESSORS_CONF);
    if(cpu_which<0 || cpu_which>cpu_num) {
        printf("[%s]cpu_which:false:cpu_num=%d cpu_which=%d\n",__FUNCTION__,cpu_num,cpu_which);
        return;
    }
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_which,&mask);
    if(sched_setaffinity(0,sizeof(mask),&mask)==-1) {
        printf("[%s]sched_setaffinity:false:cpu_num=%d cpu_which=%d\n",__FUNCTION__,cpu_num,cpu_which);
        return;
    }
    else {
        printf("[%s]sched_setaffinity:true:cpu_num=%d cpu_which=%d\n",__FUNCTION__,cpu_num,cpu_which);
    }
 }

static void vSetThreadPriority(int priority)
{
    if(priority<0||priority>99) {
        printf("[%s]error:%d:thread priority is [0,99]",__FUNCTION__,priority);
        return;
    }
    int policy=SCHED_FIFO;
    struct sched_param sp;
    sp.sched_priority=priority;
    
    int res=pthread_setschedparam(pthread_self(),policy,&sp);
    if(res!=0) {
        printf("[%s]pthread_setschedparam:error:%d SetThreadPriority:need root authority\n",__FUNCTION__,res);
        return;
    }
    printf("[%s]thread priority:%d\n",__FUNCTION__,priority);
}

static void vGetThreadPriority()
{
    int policy=SCHED_FIFO;
    struct sched_param sp;
    pthread_getschedparam(pthread_self(),&policy,&sp);

    if(policy==SCHED_OTHER) {
        printf("[%s]policy:SCHED_OTHER:%d\n",__FUNCTION__,sp.sched_priority);
    }
    else if(policy==SCHED_FIFO) {
        printf("[%s]policy:SCHED_FIFO:%d\n",__FUNCTION__,sp.sched_priority);
    }
    else if(policy==SCHED_RR) {
        printf("[%s]policy:SCHED_RR:%d\n",__FUNCTION__,sp.sched_priority);
    }
}
#endif