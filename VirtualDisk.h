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

//��������࣬���̽ӿڣ����浱ǰ��Ŀ¼���Լ����û����������ݸ�������ִ��
class VirtualDisk
{
public:
	static VirtualDisk* Instance(); //��ȡ����ָ��
	void GetCmdStr(); //���ִ�������ַ���
	bool ExecuteCmd(string input_str); //ִ������
	void SplitInput(const string input_str, list<string> &input_list_str);//�������ַ����ָ�Ϊ�б�
	string GetCurPath(); //��õ�ǰ·��
	
private:
	VirtualDisk();
	virtual ~VirtualDisk();

private:
	static VirtualDisk *instance; //����ָ��
	class Garbo //����������
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
	Factory* factory; //�����ָ��
	FileDisk* filedisk; //�����ļ�ָ��
	DiskPath* diskpath; //����·��ָ��
};

