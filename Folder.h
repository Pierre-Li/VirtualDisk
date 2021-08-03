#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "File.h"
#include "SymbolLink.h"

//文件夹类，涉及文件夹添加、移除，查找文件，以及显示目录列表信息

class Folder : public Component
{
public:
	map<string , Component*> cmap_;//目录表，存放当前目录下的文件信息,参数：键;文件名,值;组件

public:
	Folder(Component*, const string&, int);//参数：父节点，名字，类型
	~Folder();

public:
	void DisplayAll();//遍历map显示信息
	void Add(const string &component_name, int component_type); //添加文件，参数：文件名，类型
	void Remove(const string &component_name);//删除文件
	void RecurRemove(Component* component, const string &component_name);//递归删除文件
	Component* GetNodeByName(const string &component_name);//通过名字获取组件节点

public:
	void DisplayFolder();//显示子目录信息
	void DisplayFile();//显示目录及其子目录下的所有文件
	void RecurTraversel(Component* component, int &all_size);//递归遍历
};