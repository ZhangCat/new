
#ifndef VFILE_HPP
#define VFILE_HPP

#include <cstdio>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <string>

static int vFileExist(const std::string fname)
{
    return access(fname.data(),0)==0?-1:0;
}

static int vFileSize(const std::string fname)
{
    struct stat statbuf;
    return stat(fname.data(),&statbuf)==0?statbuf.st_size:-1;
}

static int vFileDelete(const std::string fname)
{
    return remove(fname.data());
}

static int vFileMove(const std::string fname1,const std::string fname2)
{
    return rename(fname1.data(),fname2.data());
}

static int vFileWrite(const std::string fname,const std::string& data)
{
    std::fstream fs(fname.data(),std::fstream::out|std::fstream::app);
    if(fs.good())
    {   
        fs.write(data.data(),data.size());
        fs.close();
        return data.size();
    }
    else
    {
        return -1;
    }
}

static int vFileWrite(const std::string fname,const char* data,int size)
{
    std::fstream fs(fname.data(),std::fstream::out|std::fstream::app);
    if(fs.good())
    {   
        fs.write(data,size);
        fs.close();
        return size;
    }
    else
    {
        return -1;
    }
}

#endif