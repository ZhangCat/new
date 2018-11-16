
#ifndef THREAD_PROPERTY_H
#define THREAD_PROPERTY_H

#include <pthread.h>
#include <sched.h>
#include <unistd.h>

#ifdef _cplusplus
extern "C" {
#endif

void SetThreadAffinity(pthread_t thread_id,int cpu_num);
void SetThreadPriority(pthread_t thread_id,int priority);

#ifdef _cplusplus
extern "C" }
#endif

#endif