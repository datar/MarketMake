#include <iostream>
#include <iomanip>

#include "HSUtils.h"
#include "TimeInfo.h"
#include "TradeSystem.h"

#include "CallBack.h"

using namespace std;

//接口查询
unsigned long  HSAPI CMyCallBack::QueryInterface( const char *, IHSKnown **){
    return 0;
}

//引用接口，引用计数加一
unsigned long  HSAPI CMyCallBack::AddRef(){
    return 0;
}

//释放接口，引用计数减一，计数为0时释放接口的实现对象
unsigned long  HSAPI CMyCallBack::Release(){
    return 0;
}

void HSAPI CMyCallBack::OnNotifyConnState(IHsFutuComm* lpComm,int iType,int iStatus,const char* szNotifyTime,const char* szMessage)	{
	cout<<"通信状态改变:"<<iType<<" : "<< setw(2)<<iStatus<<" : "<<szNotifyTime<<" : "<<szMessage<<endl;

    //连接断开了
	if((iStatus == 0) && !g_bStop){
		g_iType = iType;
		SetEvent(g_hEvent);
	}
}

//登陆反馈
void HSAPI CMyCallBack::OnRspLogin(IHsFutuComm* lpComm,IFuMessage* lpMsg){
	cout<<"登陆反馈:"<<lpMsg->GetRecord()->GetCount()<<endl;
	lpMsg->AddRef();
	ShowFuMessage(lpMsg);
}

//登出反馈
void HSAPI CMyCallBack::OnRspLogout(IHsFutuComm* lpComm,IFuMessage* lpMsg){
	cout<<"登出反馈:"<<endl;
	ShowFuMessage(lpMsg);
}

//定义反馈
void  HSAPI CMyCallBack::OnRspSubResult(IHsFutuComm* lpComm,REGType sType,REGAction aType,int iResult,const char* lpParam,const char* szMessage)	{
	cout<<"订阅结果反馈:type="<<sType<<" action="<<aType<<" result="<<iResult<<" param="<<(lpParam?lpParam:"(null)")<<" message="<<szMessage<<endl;
}

//接收到业务应答消息
void HSAPI CMyCallBack::OnReceivedBiz(IHsFutuComm* lpComm,IFuMessage* lpAnsData,int iRet,int iKeyID){
	g_Counter.Stop();
	cout<<"收到业务消息，异步处理耗时:"<<g_Counter.Elapse()<<" iRet="<<iRet<<"KeyID="<<iKeyID<<endl;
    ShowFuMessage(lpAnsData);
}

//接收到单腿市场行情
void HSAPI CMyCallBack::OnRecvMarketData(IHsFutuComm* lpComm,CMarketInfo* lpInfo,REGAction rAction){
    char timeStr[TimeInfo::MAX_TIME_INFO_LENGTH];
    TimeInfo::getNowTimeStr(timeStr);
    Quote.addHSQuote(timeStr, lpInfo);
    
    cout<<timeStr<<"--"<<QuoteData2Str(*lpInfo)<<endl;
}

//接收到组合市场行情
void HSAPI CMyCallBack::OnRecvArgMarketData(IHsFutuComm* lpComm,CArgMarketInfo* lpInfo,REGAction rAction){
	cout<<"组合行情:("<<lpInfo->futu_exch_type<<":"<<lpInfo->arbicontract_id<<")"<<endl;
}

//接收到委托反馈消息
void HSAPI CMyCallBack::OnRecvOrderInfo(IHsFutuComm* lpComm,const COrderRspInfo* lpInfo){
	cout<<"委托反馈:(fund_account="<<lpInfo->fund_account<<" : entrust_no="<<lpInfo->entrust_no<<")"<<endl;
}

//接收到成交反馈
void HSAPI CMyCallBack::OnRecvOrderRealInfo(IHsFutuComm* lpComm,const CRealRspInfo* lpInfo){
	cout<<"成交反馈:(";
	cout<<"fund_account="<<lpInfo->fund_account<<";";
	cout<<" entrust_no="<<lpInfo->entrust_no<<";";
	cout<<"entrust_bs="<<lpInfo->entrust_bs<<";";
	cout<<"entrust_direction="<<lpInfo->entrust_direction<<";";
	cout<<"hedge_type="<<lpInfo->hedge_type<<";";
	cout<<"futu_exch_type="<<lpInfo->futu_exch_type;
	cout<<")"<<endl;

}

//个人在线消息
void HSAPI CMyCallBack::OnRspOnlineMsg(IHsFutuComm* lpComm,const char* szUsrID,const char* szMessage){
	cout<<"在线消息:(user="<<(szUsrID?szUsrID:"(null)")<<" message="<<szMessage<<")"<<endl;
}

void HSAPI CMyCallBack::OnRecvExchStatsInfo(IHsFutuComm* lpComm,const CExchStatusInfo* lpInfo){

}