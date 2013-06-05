#pragma once

#include "HSFutures.h"
 
//异步回调接口的实现
class CMyCallBack:public IFuCallBack{
public:
	//接口查询
	unsigned long  HSAPI QueryInterface( const char *, IHSKnown **);
	//引用接口，引用计数加一
	unsigned long  HSAPI AddRef();
	//释放接口，引用计数减一，计数为0时释放接口的实现对象
	unsigned long  HSAPI Release();
	
    
    //连接状态的改变
	void HSAPI OnNotifyConnState(IHsFutuComm* lpComm,int iType,int iStatus,const char* szNotifyTime,const char* szMessage);

	//登陆反馈
	void HSAPI OnRspLogin(IHsFutuComm* lpComm,IFuMessage* lpMsg);

	//登出反馈
	void HSAPI OnRspLogout(IHsFutuComm* lpComm,IFuMessage* lpMsg);

	//定义反馈
	void  HSAPI OnRspSubResult(IHsFutuComm* lpComm,REGType sType,REGAction aType,int iResult,const char* lpParam,const char* szMessage);

	//接收到业务应答消息
	void HSAPI OnReceivedBiz(IHsFutuComm* lpComm,IFuMessage* lpAnsData,int iRet,int iKeyID);

	//接收到单腿市场行情
	void HSAPI OnRecvMarketData(IHsFutuComm* lpComm,CMarketInfo* lpInfo,REGAction rAction);

	//接收到组合市场行情
	void HSAPI OnRecvArgMarketData(IHsFutuComm* lpComm,CArgMarketInfo* lpInfo,REGAction rAction);

	//接收到委托反馈消息
	void HSAPI OnRecvOrderInfo(IHsFutuComm* lpComm,const COrderRspInfo* lpInfo);

	//接收到成交反馈
	void HSAPI OnRecvOrderRealInfo(IHsFutuComm* lpComm,const CRealRspInfo* lpInfo);

	//个人在线消息
	void HSAPI OnRspOnlineMsg(IHsFutuComm* lpComm,const char* szUsrID,const char* szMessage);

    void HSAPI OnRecvExchStatsInfo(IHsFutuComm* lpComm,const CExchStatusInfo* lpInfo);
};