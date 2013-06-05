#include <iostream>
#include <sstream>
#include "Constants.h"
#include "HSUtils.h"
#include "SyncOrder.h"

using namespace std;

int SendSyncMessage(IHsFutuComm* lpComm, IFuMessage* requestMessage, IFuMessage* answerMessage){
    int HS_ErrorCode = lpComm->SyncSendRecv(requestMessage, answerMessage);
    char message[MAX_HS_ERROR_MSG_LENGTH];
    if(HS_ErrorCode != 0){
        getErrorMessage(lpComm, HS_ErrorCode, message);
    }else{
        message[0] = '\0';
    }
    //CHENXING::TODO::add_message_to_system
    ShowFuMessage(answerMessage);
    return HS_ErrorCode;
}

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
                        const char* entrust_kind){
	//业务操作委托下单
	IFuMessage* lpReqMsg = NewFuMessage(MSG_TYPE_NEW_SINGLE_ORDER,MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpAnsMsg = NewFuMessage();     //接收消息(无关消息类型和模式,SDK会置相关类型)

	//打包请求参数(字段顺序无关,重复设置字段则覆盖其值)
	IFuRecord* lpRecord = lpReqMsg->AddRecord();
	lpRecord->SetString("fund_account",username);
	lpRecord->SetString("password",password);

	lpRecord->SetString("futu_exch_type",futu_exch_type);
	lpRecord->SetString("futures_account",futures_account);
	lpRecord->SetString("contract_code",contract_code);
	lpRecord->SetString("entrust_bs", entrust_bs);
	lpRecord->SetString("futures_direction", futures_direction);
	lpRecord->SetString("hedge_type", hedge_type);
	lpRecord->SetString("futu_entrust_prop",futu_entrust_prop);
	//lpRecord->SetString("futu_entrust_price",futu_entrust_price);
    lpRecord->SetDouble("futu_entrust_price",futu_entrust_price);
	//lpRecord->SetString("entrust_amount", entrust_amount);
    lpRecord->SetInt("entrust_amount", entrust_amount);
	lpRecord->SetString("entrust_kind", entrust_kind);
    //lpRecord->SetString("volume_condition","0");
	//同步接收消息
	int iRet = SendSyncMessage(lpComm, lpReqMsg,lpAnsMsg);
    int orderNo = lpAnsMsg->GetRecord(0)->GetInt("entrust_no");
    lpReqMsg->Release();
    lpAnsMsg->Release();
    return orderNo;
}

int getSyncCombinQuote(IHsFutuComm* lpComm, 
                        const char* fund_account, 
                        const char* futu_exch_type, 
                        const char* arbicontract_id){
	//查询组合行情
	IFuMessage* lpGetCombinQuoteReqMsg = NewFuMessage(MSG_TYPE_GET_COMBIN_QUOTE,MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpGetCombinQuoteAnsMsg = NewFuMessage();     //接收消息(无关消息类型和模式,SDK会置相关类型)

	//打包请求参数(字段顺序无关,重复设置字段则覆盖其值)
	IFuRecord* lpGetCombinQuoteRecord = lpGetCombinQuoteReqMsg->AddRecord();
    lpGetCombinQuoteRecord->SetString("fund_account",fund_account);
	lpGetCombinQuoteRecord->SetString("futu_exch_type", futu_exch_type);
	lpGetCombinQuoteRecord->SetString("arbicontract_id",arbicontract_id);
	//同步接收消息
	int iRet =SendSyncMessage(lpComm, lpGetCombinQuoteReqMsg, lpGetCombinQuoteAnsMsg);

	//释放消息
	lpGetCombinQuoteReqMsg->Release();
	lpGetCombinQuoteAnsMsg->Release();

    return 0;
}

int getSyncCombinCode(IHsFutuComm* lpComm, 
                        const char* fund_account, 
                        const char* futu_exch_type, 
                        const char* request_num){
    //查询组合代码
	IFuMessage* lpGetCombinCodeReqMsg = NewFuMessage(MSG_TYPE_GET_COMBIN_CODE,MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpGetCombinCodeAnsMsg = NewFuMessage();     //接收消息(无关消息类型和模式,SDK会置相关类型)

	//打包请求参数(字段顺序无关,重复设置字段则覆盖其值)
	IFuRecord* lpGetCombinCodeRecord = lpGetCombinCodeReqMsg->AddRecord();
	lpGetCombinCodeRecord->SetString("fund_account", fund_account);
	lpGetCombinCodeRecord->SetString("futu_exch_type", futu_exch_type);
	lpGetCombinCodeRecord->SetString("request_num", request_num);
	
	int iRet = lpComm->SyncSendRecv(lpGetCombinCodeReqMsg,lpGetCombinCodeAnsMsg);
	
	//释放消息
	lpGetCombinCodeReqMsg->Release();
	lpGetCombinCodeAnsMsg->Release();
    return 0;
}

int checkSyncCombinCode(IHsFutuComm* lpComm, 
                        const char* fundAccount, 
                        const char* exchange, 
                        const char* futuresAccount, 
                        const char* contract, 
                        const char* buySell,
                        const char* openClose,
                        const char* secondContract,
                        const char* arbitrageCode){
    //组合委托代码检查
	IFuMessage* lpCheckCombinReqMsg = NewFuMessage(MSG_TYPE_CHECK_COMBIN_CODE,MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpCheckCombinAnsMsg = NewFuMessage();     //接收消息(无关消息类型和模式,SDK会置相关类型)

	//打包请求参数(字段顺序无关,重复设置字段则覆盖其值)
	IFuRecord* lpCheckCombinRecord = lpCheckCombinReqMsg->AddRecord();
	lpCheckCombinRecord->SetString("fund_account", fundAccount);
	lpCheckCombinRecord->SetString("futu_exch_type", exchange);
	lpCheckCombinRecord->SetString("futures_account", futuresAccount);
	lpCheckCombinRecord->SetString("contract_code", contract);
	lpCheckCombinRecord->SetString("entrust_bs", buySell);
	lpCheckCombinRecord->SetString("futures_direction", openClose);
	lpCheckCombinRecord->SetString("second_code", secondContract);
	lpCheckCombinRecord->SetString("arbitrage_code", arbitrageCode);
	
	int iRet = SendSyncMessage(lpComm, lpCheckCombinReqMsg, lpCheckCombinAnsMsg);
	
	lpCheckCombinReqMsg->Release();
	lpCheckCombinAnsMsg->Release();

    return 0;
}

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
                        const char* arbitrageCode){

	IFuMessage* lpReqMsg = NewFuMessage(MSG_TYPE_NEW_COMBIN_ORDER,MSG_MODE_REQUEST); 
	IFuMessage* lpAnsMsg = NewFuMessage(); 

	IFuRecord* lpRecord = lpReqMsg->AddRecord();
	lpRecord->SetString("fund_account", fundAccount);
	lpRecord->SetString("futu_exch_type", exchange);
	lpRecord->SetString("futures_account", futuresAccount);
	lpRecord->SetString("contract_code", contractCode);
	lpRecord->SetString("entrust_bs", buySell);
	lpRecord->SetString("futures_direction", openClose);
	lpRecord->SetString("hedge_type", hedgeType);
	lpRecord->SetString("futu_entrust_prop", proper);
    lpRecord->SetDouble("futu_entrust_price", price);
	lpRecord->SetInt("entrust_amount", amount);
	lpRecord->SetDouble("spring_price", springPrice);
	lpRecord->SetString("time_condition", timeCondition);
	lpRecord->SetString("valid_date", validDate);
	lpRecord->SetString("second_code", secondContract);
	lpRecord->SetString("volume_condition", volumeCondition);
	lpRecord->SetString("weave_type", weaveType);
	lpRecord->SetString("arbitrage_code", arbitrageCode);
	
	int iRet = SendSyncMessage(lpComm, lpReqMsg, lpAnsMsg);
	
	lpReqMsg->Release();
	lpAnsMsg->Release();

    return 0;
}

int queryPosition(IHsFutuComm* lpComm, 
                    const char* fundAccount, 
                    const char* beginDate, 
                    const char* endDate, 
                    const char* moneyType, 
                    const char* totalType){
    //持仓查询
	IFuMessage* lpReqMsgHOLD = NewFuMessage(MSG_TYPE_GET_BILL,MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpAnsMsgHOLD = NewFuMessage();  //接收消息(无关消息类型和模式,SDK会置相关类型)
	IFuRecord*  lpRecordHOLD = lpReqMsgHOLD->AddRecord();
	lpRecordHOLD->SetString("fund_account", fundAccount);
	lpRecordHOLD->SetString("begin_date", beginDate);
	lpRecordHOLD->SetString("end_date", endDate);
	lpRecordHOLD->SetString("money_type", moneyType);
	lpRecordHOLD->SetString("total_type", totalType);
	
    SendSyncMessage(lpComm, lpReqMsgHOLD, lpAnsMsgHOLD);

    lpReqMsgHOLD->Release();
	lpAnsMsgHOLD->Release();

    return 0;

}

int checkPassword(IHsFutuComm* lpComm){
    	//校验密码
	IFuMessage* lpGetCheckPwdReqMsg = NewFuMessage(MSG_TYPE_CHECK_PWD,MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpGetCheckPwdAnsMsg = NewFuMessage();     //接收消息(无关消息类型和模式,SDK会置相关类型)

	//打包请求参数(字段顺序无关,重复设置字段则覆盖其值)
	IFuRecord* lpGetCheckPwdRecord = lpGetCheckPwdReqMsg->AddRecord();
	lpGetCheckPwdRecord->SetString("fund_account",USER_NAME);
	lpGetCheckPwdRecord->SetString("password",USER_PWD);
	CTimeCounter t5;
	t5.Start();
	//同步接收消息
	int iRet = lpComm->SyncSendRecv(lpGetCheckPwdReqMsg,lpGetCheckPwdAnsMsg);
	t5.Stop();
	cout<<"同步委托耗时:"<<":"<<t5.Elapse()<<endl;
	if(iRet != 0){
		cout<<"同步委托失败:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}else{
		cout<<"同步委托成功!"<<endl;
	}
	ShowFuMessage(lpGetCheckPwdAnsMsg);

	//释放消息
	lpGetCheckPwdReqMsg->Release();
	lpGetCheckPwdAnsMsg->Release();

    if(0 == iRet){
		//cancel order
	}
    return 0;
}

int cancelSyncOrder(IHsFutuComm* lpComm, 
                    const char* fundAccount, 
                    const char* password, 
                    const int entrustNo){
    //撤单请求

    IFuMessage* lpReqMsg = NewFuMessage(MSG_TYPE_CANCEL_ORDER,MSG_MODE_REQUEST); 
	IFuMessage* lpAnsMsg = NewFuMessage();  
	IFuRecord* lpRecord = lpReqMsg->AddRecord();
	lpRecord->SetInt("entrust_no",entrustNo);   //委托号
	lpRecord->SetString("fund_account", username);
	lpRecord->SetString("password", password);

	int iRet = SendSyncMessage(lpComm, lpReqMsg, lpAnsMsg);
    return 0;
}

int getSingleQuote(IHsFutuComm* lpComm, 
                    const char* fundAccount,
                    const char* futuresAccount,
                    const char* contract,
                    const char* exchange,
                    const char* hedgeType){
    //查询
	IFuMessage* lpGetSingleQuoteReqMsg = NewFuMessage(MSG_TYPE_CHECK_CONTRACT_CODE, MSG_MODE_REQUEST); //委托下单
	IFuMessage* lpGetSingleQuoteAnsMsg = NewFuMessage();     
	IFuRecord* lpGetSingleQuoteRecord = lpGetSingleQuoteReqMsg->AddRecord();
	lpGetSingleQuoteRecord->SetString("fund_account", fundAccount);
	lpGetSingleQuoteRecord->SetString("futu_exch_type", exchange);
	lpGetSingleQuoteRecord->SetString("contract_code", contract);
    lpGetSingleQuoteRecord->SetString("futures_account", futuresAccount);
    lpGetSingleQuoteRecord->SetString("hedge_type", hedgeType);
	
	int iRet = SendSyncMessage(lpComm, lpGetSingleQuoteReqMsg, lpGetSingleQuoteAnsMsg);

	lpGetSingleQuoteReqMsg->Release();
	lpGetSingleQuoteAnsMsg->Release();

    return 0;
}