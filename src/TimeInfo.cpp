#include <ctime>

#include "TimeInfo.h"

using namespace std;

namespace TimeInfo{

const char* DEFAULT_TIME_FORMAT = "%Y.%m.%d %H:%M:%S";

char* getNowTimeStr(const char* format, char* result){
    time_t rawtime;
    time (&rawtime);
    strftime (result, MAX_TIME_INFO_LENGTH, format, localtime (&rawtime));
    return result;
}

char* getNowTimeStr(char* result){
    return getNowTimeStr(DEFAULT_TIME_FORMAT, result);
}



}