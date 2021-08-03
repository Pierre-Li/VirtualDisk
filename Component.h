#pragma once
#include <map>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "NowTime.h"
#include "StringDeal.h"
using namespace std;

//文件类型枚举
enum FileType
{
	TYPE_NOT_HAVE = 0, //其他类型
	TYPE_FOLDER = 1, //文件夹类型
	TYPE_FILE = 2, //文件类型
	TYPE_LINK_FOLDER = 3,//链接文件夹
	TYPE_LINK_FILE = 4,//链接文件夹
};

//组件类，包含文件，文件夹，符号链接的公共部分；属性：名字，时间，大小，类型，父节点
class Component
{
public:
	Component(Component *father_node, const string &name, int type);//参数：组件父节点，名字，类型
	virtual ~Component();

public:
	int GetType() const; //获得文件类型
	int GetSize() const; //获得文件大小
	const string& GetName()const; //获得文件名
	const string& GetTime()const; //获得文件日期，时间
	string GetTypeName() const; //获得文件类型名
	Component* GetFaterNode() const; //获得文件父节点
	void SetSize(int size); //设置文件大小
	void SetName(string & name); //设置文件名
	void SetTime(string & time); //设置日期，时间
	void SetFatherNode(Component *father_node); //设置父节点

public:
	virtual void Display(); //显示文件信息
	virtual void Add(const string & name, int type); //创建文件
	virtual void Remove(const string &name); //删除文件
	virtual Component* GetNodeByName(const string &name); //通过文件名找文件节点，返回：组件节点

private:
	string name_; //文件名称
	string time_; //文件时间
	int size_; //文件大小
	int type_; //文件类型
	Component* father_node_; //文件符目录
};

