#pragma once
#include "Component.h"


class File : public Component
{
public:
	File(Component *, const string &, const int); //���������ڵ㣬���֣�����
	~File();

public:
	bool WriteContent(vector<unsigned char> content, const int); //������д���ļ���
	vector<unsigned char> GetContent(int &content_size) const; //����ļ������ݣ��������ļ���С

private:
	vector<unsigned char> content_; //�ļ��ڲ�����
};