#pragma once
#include <iostream>
#include <list>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

//�����ַ���,���ܣ��ж��Ƿ�ͨ�������intתstring
class StringDeal
{
public:
	StringDeal();
	~StringDeal();

public:
	static string IntToString(int all_file_size);//���intת��Ϊ�ַ�����ÿ��λ�ö��Ÿ���
	static bool IsHaveWildCard(const string &name);//�ж��Ƿ���ͨ���
	static bool MatchsWildCard(const string wild_card, const string str_name);//�ж��ļ������Ƿ����ͨ���
};

