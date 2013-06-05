#pragma once
#include <Windows.h>

#include "futu_data_types.h"
#include "futu_message_interface.h"
#include "futu_sdk_interface.h"

#include "CTimeCounter.h"

#define pause _getch

//Global names for HengSheng system
static const char* const HS_FIELD_FUTU = "futu";
static const char* const HS_SECTION_

//Global
extern CTimeCounter g_Counter;

//auto connect
extern HANDLE        g_hEvent;
extern volatile int  g_iType;
extern volatile bool g_bStop;