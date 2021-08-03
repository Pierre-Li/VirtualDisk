#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "File.h"
#include "SymbolLink.h"

//�ļ����࣬�漰�ļ�����ӡ��Ƴ��������ļ����Լ���ʾĿ¼�б���Ϣ

class Folder : public Component
{
public:
	map<string , Component*> cmap_;//Ŀ¼����ŵ�ǰĿ¼�µ��ļ���Ϣ,��������;�ļ���,ֵ;���

public:
	Folder(Component*, const string&, int);//���������ڵ㣬���֣�����
	~Folder();

public:
	void DisplayAll();//����map��ʾ��Ϣ
	void Add(const string &component_name, int component_type); //����ļ����������ļ���������
	void Remove(const string &component_name);//ɾ���ļ�
	void RecurRemove(Component* component, const string &component_name);//�ݹ�ɾ���ļ�
	Component* GetNodeByName(const string &component_name);//ͨ�����ֻ�ȡ����ڵ�

public:
	void DisplayFolder();//��ʾ��Ŀ¼��Ϣ
	void DisplayFile();//��ʾĿ¼������Ŀ¼�µ������ļ�
	void RecurTraversel(Component* component, int &all_size);//�ݹ����
};