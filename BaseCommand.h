#pragma once
#include "DiskPath.h"
#include "FileDisk.h"
#include "TrueDiskOper.h"
#include "Component.h"
#include "DiskPath.h"
#include <deque>

//命令的基类,实现命令的基本操作
class BaseCommand
{
public:
	BaseCommand();
	virtual ~BaseCommand();

public:
	virtual bool ExecuteCmd(DiskPath *cur_path, list<string> &input_path_list, FileDisk *file_disk) = 0;//命令执行函数，参数：磁盘路径；命令操作路径；磁盘文件，返回操作是否成功
	void GetArgAndPath(list<string> arg_path_list, list<string> &arg_list, list<string> &path_list);//获得输入的参数与路径
	void DealListPath(list<string> input_path, list<string> &deal_path, DiskPath *disk_path);//处理列表路径，将相对路径转绝对路径
	void DealStrPath(const string &input_path, list<string> &deal_path, DiskPath *disk_path);//处理字符串路径，将相对路径转绝对路径
};

//显示命令
class CommandDir : public BaseCommand
{
public:
	CommandDir();
	~CommandDir();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//创建命令
class CommandMd : public BaseCommand
{
public:
	CommandMd();
	~CommandMd();
	
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//删除目录命令
class CommandRd : public BaseCommand
{
public:
	CommandRd();
	~CommandRd();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void ComponentRemove(Component* node, int flag);//文件或文件夹删除
	void LinkRemove(Component* node1, Component* node2, int flag);//链接文件删除
};

//切换目录命令
class CommandCd : public BaseCommand
{
public:
	CommandCd();
	~CommandCd();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//删除文件命令
class CommandDel : public BaseCommand
{
public:
	CommandDel();
	~CommandDel();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void DelComponent(Component* node, int flag);

};

//拷贝文件
class CommandCopy : public BaseCommand
{
public:
	CommandCopy();
	~CommandCopy();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void FileCopy(Component* file, Component* path_node); //虚拟磁盘文件copy
	void FolderCopy(Component* path_node1, Component* path_node2); //虚拟磁盘文件夹copy
	void TrueFileCopy(string true_path, string file_name, Component* path_node); //真实路径文件copy
};

//重命名命令
class CommandRen : public BaseCommand
{
public:
	CommandRen();
	~CommandRen();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	bool NameIsLegal(string new_name);
};

//移动命令
class CommandMove : public BaseCommand
{
public:
	CommandMove();
	~CommandMove();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void ComponentMove(Component* node1, Component* node2, int flag);//文件或文件夹移动
	bool ContainPath(Component* node1, Component* node2);//判断路径之间是否包含
};

//创建符号链接
class CommandMklink : public BaseCommand
{
public:
	CommandMklink();
	~CommandMklink();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//虚拟磁盘保存命令
class CommandSave : public BaseCommand
{
public:
	CommandSave();
	~CommandSave();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//加载虚拟磁盘命令
class CommandLoad : public BaseCommand
{
public:
	CommandLoad();
	~CommandLoad();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//清屏
class CommandCls : public BaseCommand
{
public:
	CommandCls();
	~CommandCls();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

