#pragma warning(disable:4996)
#include <string>
using namespace std;

//��ȡʱ��
class NowTime
{
public:
	static NowTime* Instance(); //��ȡ����ָ��
	string GetNowTime(); //��ȡ��ǰʱ��
	
private:
	NowTime();
	~NowTime();

private:
	static NowTime *instance;//����ָ��
};

