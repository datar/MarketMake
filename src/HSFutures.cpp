#include "HSFutures.h"
#include "CTimeCounter.h"

//全局变量
CTimeCounter g_Counter;


//自动重连线程相关
HANDLE        g_hEvent = NULL;
volatile int  g_iType = 0;
volatile bool g_bStop = false;
