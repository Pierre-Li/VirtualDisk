#pragma once
#include "Component.h"
#include "Folder.h"

//磁盘类，创建根节点，格式化磁盘
class FileDisk
{
public:
	Component* root; //磁盘根节点

public:
	FileDisk();
	~FileDisk();

public:
	void FormatDisk(); //初始化磁盘
	void SetRootNode(Component*); //设置根节点
	Component* GetRootNode(); //获取根节点
};

