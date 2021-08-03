#pragma once
#include <cstdio>
#include <string>
#include <algorithm>
#include "Factory.h"
#include "FileDisk.h"
#include "DiskPath.h"
#include "StringDeal.h"
#include "BaseCommand.h"
#include <iostream>
using namespace std;

//虚拟磁盘类，磁盘接口，保存当前根目录，以及将用户输入的命令传递给其他类执行
class VirtualDisk
{
public:
	static VirtualDisk* Instance(); //获取单例指针
	void GetCmdStr(); //获得执行命令字符串
	bool ExecuteCmd(string input_str); //执行命令
	void SplitInput(const string input_str, list<string> &input_list_str);//将输入字符串分割为列表
	string GetCurPath(); //获得当前路径
	
private:
	VirtualDisk();
	virtual ~VirtualDisk();

private:
	static VirtualDisk *instance; //单例指针
	class Garbo //垃圾回收类
	{
	public:
		~Garbo()
		{
			if (VirtualDisk::instance)
			{
				delete VirtualDisk::instance;
				VirtualDisk::instance = NULL;
			}	
		}
	};
	static Garbo garbo;

private:
	Factory* factory; //命令工厂指针
	FileDisk* filedisk; //磁盘文件指针
	DiskPath* diskpath; //磁盘路径指针
};

