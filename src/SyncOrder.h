#pragma once

#include <string>

#include "HSFutures.h"
#include "SyncOrder.h"

using namespace std;

int SendSyncMessage(IHsFutuComm* lpComm, IFuMessage* requestMessage, IFuMessage* answerMessage);

int sendSyncSingleOrder(IHsFutuComm* lpComm,
                        const char* fundAccount,
                        const char* password,
                        const char* exchange,
                        const char* futuresAccount,
                        const char* contractCode,
                        const char* buySell,
                        const char* openClose,
                        const char* hedgeType,
                        const char* proper,
                        const double price,
                        const int amount,
                        const char* kind);

int getSyncCombinQuote(IHsFutuComm* lpComm, 
                        const char* fund_account, 
                        const char* futu_exch_type, 
                        const char* arbicontract_id);

int getSyncCombinCode(IHsFutuComm* lpComm, 
                        const char* fund_account, 
                        const char* futu_exch_type, 
                        const char* request_num);

int checkSyncCombinCode(IHsFutuComm* lpComm, 
                        const char* fundAccount, 
                        const char* exchange, 
                        const char* futuresAccount, 
                        const char* contract, 
                        const char* buySell,
                        const char* openClose,
                        const char* secondContract,
                        const char* arbitrageCode);

int sendSyncCombinOrder(IHsFutuComm* lpComm,
                        const char* fundAccount,
                        const char* exchange,
                        const char* futuresAccount,
                        const char* contractCode,
                        const char* buySell,
                        const char* openClose,
                        const char* hedgeType,
                        const char* proper,
                        const double price,
                        const int amount,
                        const double springPrice,
                        const char* timeCondition,
                        const char* validDate,
                        const char* secondContract,
                        const char* volumeCondition,
                        const char* weaveType,
                        const char* arbitrageCode);

int queryPosition(IHsFutuComm* lpComm, 
                    const char* fundAccount, 
                    const char* beginDate, 
                    const char* endDate, 
                    const char* moneyType, 
                    const char* totalType);
int checkPassword(IHsFutuComm* lpComm);

int cancelSyncOrder(IHsFutuComm* lpComm, 
                    const char* fundAccount, 
                    const char* password, 
                    const int entrustNo);

int getSingleQuote(IHsFutuComm* lpComm, 
                    const char* fundAccount,
                    const char* futuresAccount,
                    const char* contract,
                    const char* exchange,
                    const char* hedgeType);