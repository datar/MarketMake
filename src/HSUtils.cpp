
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#include "Constants.h"
#include "HSUtils.h"

DWORD WINAPI auto_connect(void* lpParam){
	IHsFutuComm* lpComm = (IHsFutuComm*)lpParam;
	while(!g_bStop){
		if(WAIT_OBJECT_0 == WaitForSingleObject(g_hEvent,INFINITE)){
			//退出
			if(g_bStop){
				cout<<"自动重连线程退出!"<<endl;
				return 0;
			}

			cout<<"检测连接端口,开始自动重连......"<<endl;
			//重连
			for (int iRet = 0;;){
				if(0 == (iRet = lpComm->Start(g_iType))){
					ResetEvent(g_hEvent);
					break;
				}
				cout<<"线程自动重连失败:"<<lpComm->GetErrorMsg(iRet)<<endl;
				//重连失败,暂停一会儿再试
				Sleep(1000);
			}
		}
	}
	cout<<"自动重连线程退出!"<<endl;
	return 0;
}


int getErrorMessage(IHsFutuComm* comm, int errorCode, char* message){
    return sprintf(message, "[%d]:%s", errorCode, comm->GetErrorMsg(errorCode));
}


//显示整条消息
void ShowFuMessage(IFuMessage* lpMessage){
	cout<<"======================<<IFuMessage BEGIN>>====================="<<endl;
	cout<<"nRecords:"<<lpMessage->GetCount()
		<<" MsgType:"<<lpMessage->GetMsgType()
		<<((lpMessage->GetCount()<=0)?" (应答结果集为空)":"")<<endl;
	for (int i=0;i<lpMessage->GetCount();++i){
		IFuRecord* lpRecord = lpMessage->GetRecord(i);
		cout<<"Record ["<<i+1<<"]:"<<endl;
		for (lpRecord->MoveFirst();!lpRecord->IsEOF();lpRecord->MoveNext()){
			const char* strField = lpRecord->GetFieldName();
			cout.width(20);
			cout<<strField<<" : "<<lpRecord->GetString(strField)<<endl;
		}
		cout<<endl;
	}
	cout<<"=======================<<IFuMessage END>>======================"<<endl;
}

void GetFuMessageString(IFuMessage* message, string& result){
    ostringstream out;
    out<<"======================<<IFuMessage BEGIN>>====================="<<endl;
	out<<"nRecords:"<<message->GetCount()
		<<" MsgType:"<<message->GetMsgType()
		<<((message->GetCount()<=0)?" (应答结果集为空)":"")<<endl;
	for (int i = 0; i < message->GetCount(); ++i){
		IFuRecord* lpRecord = message->GetRecord(i);
		out<<"Record ["<<i+1<<"]:"<<endl;
		for (lpRecord->MoveFirst();!lpRecord->IsEOF();lpRecord->MoveNext()){
			const char* strField = lpRecord->GetFieldName();
			out.width(20);
			out<<strField<<" : "<<lpRecord->GetString(strField)<<endl;
		}
		out<<endl;
	}
	out<<"=======================<<IFuMessage END>>======================"<<endl;
    result = out.str();
}

int message2String(IFuMessage* message, char* result, unsigned int maxLength){
    int count = message->GetCount();
    sprintf(result, "MsgType=%d,RecordNum=%d", message->GetMsgType(), count);
    char recordStr[MAX_HS_MSG_RECORD_STR_LENGTH];
    for (int i=0;i<message->GetCount();++i){
		IFuRecord* record = message->GetRecord(i);
        sprintf(recordStr, ",Record [%d]=", i);
        strcat(result, recordStr);
		for (record->MoveFirst();!record->IsEOF();record->MoveNext()){
			const char* strField = record->GetFieldName();
            sprintf(recordStr, "|%s:%s|", strField, record->GetString(strField));
            strcat(result, recordStr);
		}
    }
    return strlen(result);
}

int saveFuturesMessage(IFuMessage* message){

    return 0;
}