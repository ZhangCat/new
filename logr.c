
#ifdef NOLOG
#define logr(...)
#else
#define LOGPATH "/sdcard/demolog/"
#define MNAME "demo"
static FILE *fp_log=NULL;
#define logr(...) do{\
struct timeval tv;gettimeofday(&tv,NULL);\
struct tm *tma;tma=localtime(&tv.tv_sec);\
if(access(LOGPATH,0)==0&&fp_log==NULL){\
	fp_log=fopen(LOGPATH MNAME ".log","w+");}\
if(fp_log){fprintf(fp_log,"[%d-%02d-%02d %02d:%02d:%02d.%06ld]",\
	tma->tm_year+1900,tma->tm_mon+1,tma->tm_mday,\
	tma->tm_hour,tma->tm_min,tma->tm_sec,tv.tv_usec);\
	fprintf(fp_log,"[%s][%s][%d]:",MNAME,__FUNCTION__,__LINE__);\
	fprintf(fp_log,__VA_ARGS__);\
	fflush(fp_log);}\
else{printf("[%d-%02d-%02d %02d:%02d:%02d.%06ld]",\
	tma->tm_year+1900,tma->tm_mon+1,tma->tm_mday,\
	tma->tm_hour,tma->tm_min,tma->tm_sec,tv.tv_usec);\
	printf("[%s][%s][%d]:",MNAME,__FUNCTION__,__LINE__);\
	printf(__VA_ARGS__);}}while(0)
#endif