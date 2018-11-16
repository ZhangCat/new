
#ifndef VTOOL_HPP
#define VTOOL_HPP

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int filesize(const char *filename);

#ifdef __cplusplus
}
#endif

int filesize(const char *filename)
{
    FILE *fp=fopen(filename,"rb");
    if(fp)
    {
        fseek(fp,0L,SEEK_END);
        int size=ftell(fp);
        fclose(fp);
        return size;
    }
    return -1;
}

#endif