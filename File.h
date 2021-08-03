#pragma once
#include "Component.h"


class File : public Component
{
public:
	File(Component *, const string &, const int); //参数：父节点，名字，类型
	~File();

public:
	bool WriteContent(vector<unsigned char> content, const int); //将数据写入文件中
	vector<unsigned char> GetContent(int &content_size) const; //获得文件的数据，参数：文件大小

private:
	vector<unsigned char> content_; //文件内部数据
};