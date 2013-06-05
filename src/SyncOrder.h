#pragma once

#include <string>

#include "HSFutures.h"
#include "SyncOrder.h"

using namespace std;

int sendSyncSingleOrder(IHsFutuComm* lpComm);

int sendSyncSingleOrder(IHsFutuComm* lpComm,
                        const char* username,
                        const char* password,
                        const char* futu_exch_type,
                        const char* futures_account,
                        const char* contract_code,
                        const char* entrust_bs,
                        const char* futures_direction,
                        const char* hedge_type,
                        const char* futu_entrust_prop,
                        const double futu_entrust_price,
                        const int entrust_amount,
                        const char* entrust_kind);

int getSyncCombinQuote(IHsFutuComm* lpComm);
int getSyncCombinCode(IHsFutuComm* lpComm);
int checkSyncCombinCode(IHsFutuComm* lpComm);
int sendSyncCombinOrder(IHsFutuComm* lpComm);
int queryPosition(IHsFutuComm* lpComm);
int checkPassword(IHsFutuComm* lpComm);
int cancelSyncOrder(IHsFutuComm* lpComm, int entrust_no);
int getSingleQuote(IHsFutuComm* lpComm, string contract);