#pragma once
#include "Component.h"
#include "Folder.h"

//�����࣬�������ڵ㣬��ʽ������
class FileDisk
{
public:
	Component* root; //���̸��ڵ�

public:
	FileDisk();
	~FileDisk();

public:
	void FormatDisk(); //��ʼ������
	void SetRootNode(Component*); //���ø��ڵ�
	Component* GetRootNode(); //��ȡ���ڵ�
};

