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

//�ļ�����ö��
enum FileType
{
	TYPE_NOT_HAVE = 0, //��������
	TYPE_FOLDER = 1, //�ļ�������
	TYPE_FILE = 2, //�ļ�����
	TYPE_LINK_FOLDER = 3,//�����ļ���
	TYPE_LINK_FILE = 4,//�����ļ���
};

//����࣬�����ļ����ļ��У��������ӵĹ������֣����ԣ����֣�ʱ�䣬��С�����ͣ����ڵ�
class Component
{
public:
	Component(Component *father_node, const string &name, int type);//������������ڵ㣬���֣�����
	virtual ~Component();

public:
	int GetType() const; //����ļ�����
	int GetSize() const; //����ļ���С
	const string& GetName()const; //����ļ���
	const string& GetTime()const; //����ļ����ڣ�ʱ��
	string GetTypeName() const; //����ļ�������
	Component* GetFaterNode() const; //����ļ����ڵ�
	void SetSize(int size); //�����ļ���С
	void SetName(string & name); //�����ļ���
	void SetTime(string & time); //�������ڣ�ʱ��
	void SetFatherNode(Component *father_node); //���ø��ڵ�

public:
	virtual void Display(); //��ʾ�ļ���Ϣ
	virtual void Add(const string & name, int type); //�����ļ�
	virtual void Remove(const string &name); //ɾ���ļ�
	virtual Component* GetNodeByName(const string &name); //ͨ���ļ������ļ��ڵ㣬���أ�����ڵ�

private:
	string name_; //�ļ�����
	string time_; //�ļ�ʱ��
	int size_; //�ļ���С
	int type_; //�ļ�����
	Component* father_node_; //�ļ���Ŀ¼
};

