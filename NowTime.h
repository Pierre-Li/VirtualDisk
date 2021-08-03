#pragma warning(disable:4996)
#include <string>
using namespace std;

//获取时间
class NowTime
{
public:
	static NowTime* Instance(); //获取单例指针
	string GetNowTime(); //获取当前时间
	
private:
	NowTime();
	~NowTime();

private:
	static NowTime *instance;//单例指针
};

