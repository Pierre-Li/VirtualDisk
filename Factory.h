#pragma once
#include <string>
#include <iostream>
#include "BaseCommand.h"
using namespace std;

//�������������Ӧ����ִ�к���
class Factory
{
public:
	Factory();
	~Factory();

public:
	BaseCommand* CreateCommand(const string& command_name);//������Ӧ����ִ�к���
};

