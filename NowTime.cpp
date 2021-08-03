#include "NowTime.h"
#include <time.h>
#include "StringDeal.h"
#include <atlbase.h>
#include <atlconv.h>

NowTime* NowTime::instance = 0;

NowTime::NowTime()
{
}


NowTime* NowTime::Instance()
{
	if (instance == 0)
	{
		instance = new NowTime();
	}
	return instance;
}

//获取当前时间
string NowTime::GetNowTime()
{
	
	time_t t = time(0);
	char time_str[64] = {0};
	strftime(time_str, sizeof(time_str), "%Y/%m/%d  %H:%M", localtime(&t));
	string now_time = time_str;
	return now_time;
}

NowTime::~NowTime()
{
}