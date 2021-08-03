#pragma once
#include "Component.h"

class SymbolLink :public Component
{
public:
	SymbolLink(Component *, const string &, int);
	~SymbolLink();

public:
	void SetLink(const string &); //设置链接文件
	void Display() override; //显示链接类型文件
	string GetLink(); //获得链接文件指向路径
	list<string> GetListLinkpath(); //获得列表类型的链接文件指向路径

private:
	string link_path_; //链接文件指向的路径
};

