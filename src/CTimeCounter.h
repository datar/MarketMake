#pragma once

#include <Windows.h>

///高精度计时器,单位毫秒
class CTimeCounter{
public:
	//构造函数
	CTimeCounter(){
        QueryPerformanceFrequency(&hz);
    }
	//开始计时
	inline void Start(){
        QueryPerformanceCounter(&rs);
    }
	//从开始计时逝去的时间
	inline long double Elapse(){
		return (( now.QuadPart-rs.QuadPart)/(long double)hz.QuadPart)*1000;
	}
	inline void Stop(){QueryPerformanceCounter(&now);}
private:
	LARGE_INTEGER hz;
	LARGE_INTEGER rs;
	LARGE_INTEGER now;
};