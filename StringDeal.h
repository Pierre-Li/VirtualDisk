#pragma once
#include <iostream>
#include <list>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

//处理字符串,功能：判断是否含通配符，将int转string
class StringDeal
{
public:
	StringDeal();
	~StringDeal();

public:
	static string IntToString(int all_file_size);//输出int转换为字符串，每三位用逗号隔开
	static bool IsHaveWildCard(const string &name);//判断是否含有通配符
	static bool MatchsWildCard(const string wild_card, const string str_name);//判断文件名称是否符合通配符
};

