//
//  SGLog.cpp
//  Legend
//
//  Created by soulghost on 5/1/2018.
//
//

#include "SGLog.h"
#include <time.h>
#include <sys/timeb.h>
#include <sstream>

const char* log_time(void) {
    struct  tm      *ptm;
    struct  timeb   stTimeb;
    static  char    szTime[27];
    
    ftime(&stTimeb);
    ptm = localtime(&stTimeb.time);
    sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
            ptm->tm_year + 1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm);
    szTime[26] = 0;
    return szTime;
}

void SGLog::info(const char *format, ...) {
#ifdef COCOS2D_DEBUG
    const char *head = "[Legend Log Info]";
    const char *time = log_time();
    char fmt[2048];
    sprintf(fmt, "%s %s %s", time, head, format);
    va_list args;
    va_start(args, format);
    cocos2d::cc_inner_log(fmt, args);
    va_end(args);
#endif
}
