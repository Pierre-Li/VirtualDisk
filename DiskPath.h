#pragma once
#include "Component.h"
#include "Folder.h"
#include "File.h"
#include <algorithm>


//��¼���̵�ǰ·����ͬʱ��·�����д���
class DiskPath
{
public:
	DiskPath();
	~DiskPath();

public:
	void SetListHead(Component *component, const string &component_name); //�����б�ͷ�ڵ� ����������������
	Component* GetRootNode(); //��ȡ���ڵ�
	string GetCurPath();//��ȡ��ǰ·��
	list<string> GetListCurPath();//��ȡ��ǰ·���б�
	void UpdateCurPath(list<string>& input_path);//��������·�������µ�ǰ·��
	void ClearDiskPath();//����б�

public:
	Component* ContainNode(list<string> &input_path);//�ж�·���Ƿ���ڴ����У���������ڵ�
	Component* ContainNodeIsSym(list<string> &input_path);//�ж����սڵ��Ƿ������Ϊ��������
	Component* ContainWildPath(list<string> &input_path, list<Component*> &component_list, int &flag);//�ж�·���Ƿ����ͨ���������������·����ƥ���·���б�ͨ�����־
	bool ListContain(Component *node, DiskPath *cur_path);//�жϽڵ��뵱ǰ·���Ƿ��غϣ�����������ڵ㣬��ǰ·��

private:
	list<pair<string , Component *>> path_list_; //��¼��ǰ·��������������������
};

