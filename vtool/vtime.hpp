#ifndef VTIME_HPP
#define VTIME_HPP
#include <cstdio>
#include <ctime>
#include <string>
#include <chrono>
#include <sys/time.h>

static const std::string vGetDateTimeStr()
{
  time_t tt=time(NULL);
  struct tm *stm=localtime(&tt);
  char tmp[50];
  sprintf(tmp, "%04d%02d%02d%02d%02d%02d",
    1900 + stm->tm_year, 1 + stm->tm_mon, stm->tm_mday,
    stm->tm_hour,stm->tm_min, stm->tm_sec);
  std::string res(tmp);
  return res;
}

static const std::string vGetDateTimeMilli()
{
  struct timeval tv;
  struct tm * time_ptr;
  gettimeofday(&tv, NULL);
  time_ptr = std::localtime(&tv.tv_sec);
  char accT[128];
  std::sprintf(accT, "%d-%02d-%02d %02d:%02d:%02d.%.04ld",
  time_ptr->tm_year + 1900,
  time_ptr->tm_mon + 1,
  time_ptr->tm_mday,
  time_ptr->tm_hour,
  time_ptr->tm_min,
  time_ptr->tm_sec,
              tv.tv_usec);
  std::string ret(accT);
  return ret;
}

static const std::chrono::steady_clock::time_point vGetTimePoint()
{
    return std::chrono::steady_clock::now();
}

static double vGetTimePointDiff(std::chrono::steady_clock::time_point t1,
    std::chrono::steady_clock::time_point t2)
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1).count()*1000;
}

#endif