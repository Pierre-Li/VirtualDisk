#pragma once
#include <string>
#include <iostream>
#include "BaseCommand.h"
using namespace std;

//命令工厂，创建对应命令执行函数
class Factory
{
public:
	Factory();
	~Factory();

public:
	BaseCommand* CreateCommand(const string& command_name);//创建对应命令执行函数
};

