#pragma once
#include "DiskPath.h"
#include "FileDisk.h"
#include "TrueDiskOper.h"
#include "Component.h"
#include "DiskPath.h"
#include <deque>

//����Ļ���,ʵ������Ļ�������
class BaseCommand
{
public:
	BaseCommand();
	virtual ~BaseCommand();

public:
	virtual bool ExecuteCmd(DiskPath *cur_path, list<string> &input_path_list, FileDisk *file_disk) = 0;//����ִ�к���������������·�����������·���������ļ������ز����Ƿ�ɹ�
	void GetArgAndPath(list<string> arg_path_list, list<string> &arg_list, list<string> &path_list);//�������Ĳ�����·��
	void DealListPath(list<string> input_path, list<string> &deal_path, DiskPath *disk_path);//�����б�·���������·��ת����·��
	void DealStrPath(const string &input_path, list<string> &deal_path, DiskPath *disk_path);//�����ַ���·���������·��ת����·��
};

//��ʾ����
class CommandDir : public BaseCommand
{
public:
	CommandDir();
	~CommandDir();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//��������
class CommandMd : public BaseCommand
{
public:
	CommandMd();
	~CommandMd();
	
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//ɾ��Ŀ¼����
class CommandRd : public BaseCommand
{
public:
	CommandRd();
	~CommandRd();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void ComponentRemove(Component* node, int flag);//�ļ����ļ���ɾ��
	void LinkRemove(Component* node1, Component* node2, int flag);//�����ļ�ɾ��
};

//�л�Ŀ¼����
class CommandCd : public BaseCommand
{
public:
	CommandCd();
	~CommandCd();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//ɾ���ļ�����
class CommandDel : public BaseCommand
{
public:
	CommandDel();
	~CommandDel();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void DelComponent(Component* node, int flag);

};

//�����ļ�
class CommandCopy : public BaseCommand
{
public:
	CommandCopy();
	~CommandCopy();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void FileCopy(Component* file, Component* path_node); //��������ļ�copy
	void FolderCopy(Component* path_node1, Component* path_node2); //��������ļ���copy
	void TrueFileCopy(string true_path, string file_name, Component* path_node); //��ʵ·���ļ�copy
};

//����������
class CommandRen : public BaseCommand
{
public:
	CommandRen();
	~CommandRen();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	bool NameIsLegal(string new_name);
};

//�ƶ�����
class CommandMove : public BaseCommand
{
public:
	CommandMove();
	~CommandMove();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
	void ComponentMove(Component* node1, Component* node2, int flag);//�ļ����ļ����ƶ�
	bool ContainPath(Component* node1, Component* node2);//�ж�·��֮���Ƿ����
};

//������������
class CommandMklink : public BaseCommand
{
public:
	CommandMklink();
	~CommandMklink();

public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//������̱�������
class CommandSave : public BaseCommand
{
public:
	CommandSave();
	~CommandSave();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//���������������
class CommandLoad : public BaseCommand
{
public:
	CommandLoad();
	~CommandLoad();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

//����
class CommandCls : public BaseCommand
{
public:
	CommandCls();
	~CommandCls();
public:
	bool ExecuteCmd(DiskPath*, list<string>&, FileDisk*) override;
};

