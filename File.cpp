#include "File.h"

File::File(Component* _father_node, const string &_name, const int _type):Component(_father_node,_name,_type)
{
	content_.clear();
}

//д�ļ�
bool File::WriteContent(vector<unsigned char> content, int content_size)
{
	content_ = content;
	SetSize(content_size);
	return true;
}

//���ļ�
vector<unsigned char> File::GetContent(int &content_size) const
{
	content_size = GetSize();
	return content_;
}

File::~File()
{
	if (content_.size())
	{
		content_.clear();
	}
}