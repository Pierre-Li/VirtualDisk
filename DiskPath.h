#pragma once
#include "Component.h"
#include "Folder.h"
#include "File.h"
#include <algorithm>


//记录磁盘当前路径，同时对路径进行处理
class DiskPath
{
public:
	DiskPath();
	~DiskPath();

public:
	void SetListHead(Component *component, const string &component_name); //设置列表头节点 参数：组件，组件名
	Component* GetRootNode(); //获取根节点
	string GetCurPath();//获取当前路径
	list<string> GetListCurPath();//获取当前路径列表
	void UpdateCurPath(list<string>& input_path);//根据输入路径，更新当前路径
	void ClearDiskPath();//清空列表

public:
	Component* ContainNode(list<string> &input_path);//判断路径是否存在磁盘中，返回组件节点
	Component* ContainNodeIsSym(list<string> &input_path);//判断最终节点是否存在且为链接类型
	Component* ContainWildPath(list<string> &input_path, list<Component*> &component_list, int &flag);//判断路径是否符合通配符，参数：输入路径，匹配的路径列表，通配符标志
	bool ListContain(Component *node, DiskPath *cur_path);//判断节点与当前路径是否重合，参数：组件节点，当前路径

private:
	list<pair<string , Component *>> path_list_; //记录当前路径，参数：组件名，组件
};

