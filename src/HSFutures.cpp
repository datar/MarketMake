#include "HSFutures.h"
#include "CTimeCounter.h"

//ȫ�ֱ���
CTimeCounter g_Counter;


//�Զ������߳����
HANDLE        g_hEvent = NULL;
volatile int  g_iType = 0;
volatile bool g_bStop = false;
