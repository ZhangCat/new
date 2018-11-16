#ifndef THREADSET_HPP
#define THREADSET_HPP

#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>

#ifdef _cplusplus
extern "C" {
#endif

void SetThreadAffinity(pthread_t thread_id,int cpu_num);
void SetThreadPriority(pthread_t thread_id,int priority);

#ifdef _cplusplus
}
#endif

void SetThreadAffinity(pthread_t thread_id,int cpu_num)
{
    int cpus = sysconf(_SC_NPROCESSORS_CONF);

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_num,&mask);

    int res=pthread_setaffinity_np(thread_id,sizeof(mask),&mask);
    if(res< 0) 
    {
        printf("[*%s*]pthread_setaffinity_np:%d:%d:error:%d\n",__FUNCTION__,cpus,cpu_num,res);
        return;
    }
    
    cpu_set_t get;
    CPU_ZERO(&get);
    res=pthread_getaffinity_np(thread_id, sizeof(get), &get);
    if(res<0) 
    {
        printf("[*%s*]pthread_getaffinity_np:error\n",__FUNCTION__);
        return;
    }

    for(int i=0;i<cpus;i++) 
    {
        if(CPU_ISSET(i,&get)) 
        {
            printf("[*%s*]cpu_sum:%d want_cpu:%d real_cpu:%d\n",__FUNCTION__,cpus,cpu_num,i); 
        }   
    }

}

void SetThreadPriority(pthread_t thread_id,int priority)
{
    int policy=SCHED_FIFO;
    struct sched_param sp;
    sp.sched_priority=priority;
    
    
    int res=pthread_setschedparam(thread_id,policy,&sp);
    if(res!=0)
    {
        printf("[*%s*]pthread_setschedparam:error:%d SetThreadPriority:need root authority\n",__FUNCTION__,res);
        return;
    }

    pthread_getschedparam(thread_id,&policy,&sp);
    printf("[*%s*]want_priority:%d real_priority:%d\n",__FUNCTION__,priority,sp.sched_priority);

    if(policy==SCHED_OTHER)
    {
        printf("[*%s*]policy:SCHED_OTHER\n",__FUNCTION__);
    }
    else if(policy==SCHED_FIFO)
    {
        printf("[*%s*]policy:SCHED_FIFO\n",__FUNCTION__);
    }
    else if(policy==SCHED_RR)
    {
        printf("[*%s*]policy:SCHED_RR\n",__FUNCTION__);
    }
}

#endif