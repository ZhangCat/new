//vov
#ifndef V_LOG_HPP
#define V_LOG_HPP

#include <sys/time.h>
#include <unistd.h>

#ifndef logv
    #ifndef VLOGFWRITE
        #define VLOGFWRITE "./fwrite.vlog"
    #endif
    #ifndef VLOGPRINTF
        #define VLOGPRINTF "./printf.vlog"
    #endif
    #define logv(...) do {\
        struct timeval tv;gettimeofday(&tv,NULL);\
        struct tm *tma;tma=localtime(&tv.tv_sec);\
        if(access(VLOGFWRITE,0)==0) {\
            FILE* fp_log=fopen(VLOGFWRITE,"a+");\
            if(fp_log) {\
                fprintf(fp_log,"[%d-%02d-%02d %02d:%02d:%02d.%06ld]",\
                tma->tm_year+1900,tma->tm_mon+1,tma->tm_mday,\
                tma->tm_hour,tma->tm_min,tma->tm_sec,tv.tv_usec);\
                fprintf(fp_log,"[vlog][%d]:",__LINE__);\
                fprintf(fp_log,__VA_ARGS__);\
                fclose(fp_log);\
            }\
        }\
        if(access(VLOGPRINTF,0)==0) {\
            printf("[%d-%02d-%02d %02d:%02d:%02d.%06ld]",\
            tma->tm_year+1900,tma->tm_mon+1,tma->tm_mday,\
            tma->tm_hour,tma->tm_min,tma->tm_sec,tv.tv_usec);\
            printf("[vlog][%d]:",__LINE__);\
            printf(__VA_ARGS__);\
        }\
    } while(0)
#endif 

#endif
