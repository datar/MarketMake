#ifndef _HENGSHNEG_UTILS_TIMEINFO_H_
#define _HENGSHNEG_UTILS_TIMEINFO_H_

namespace TimeInfo{
    
    const unsigned int MAX_TIME_INFO_LENGTH = 64;
    extern const char* DEFAULT_TIME_FORMAT;
    
    
    char* getNowTimeStr(const char* format, char* result);
    char* getNowTimeStr(char* result);
    

}
#endif