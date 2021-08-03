#pragma once
#include "Component.h"

class SymbolLink :public Component
{
public:
	SymbolLink(Component *, const string &, int);
	~SymbolLink();

public:
	void SetLink(const string &); //���������ļ�
	void Display() override; //��ʾ���������ļ�
	string GetLink(); //��������ļ�ָ��·��
	list<string> GetListLinkpath(); //����б����͵������ļ�ָ��·��

private:
	string link_path_; //�����ļ�ָ���·��
};

