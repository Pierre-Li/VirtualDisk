#include "SymbolLink.h"

SymbolLink::SymbolLink(Component* _father_node, const string &_name, int _type) :Component(_father_node, _name, _type)
{

}

//���������ļ�������·��
void SymbolLink::SetLink(const string & new_path)
{
	link_path_ = new_path;
}

//����ַ����������ļ�ָ���·��
string SymbolLink::GetLink()
{
	return link_path_;
}

//����б��������ļ�ָ���·��
list<string> SymbolLink::GetListLinkpath()
{
	list<string> list_str;
	string str;
	for (unsigned int i = 0; i < link_path_.size(); i++)
	{
		if (link_path_[i] == '/' || link_path_[i] == '\\')
		{
			list_str.push_back(str);
			str = "";
			continue;
		}
		str += link_path_[i];
	}
	list_str.push_back(str);
	return list_str;
}

//�����ļ���ʾ
void SymbolLink::Display()
{
	cout << setiosflags(ios::left) << GetTime() << "   " << left << setw(15) << GetTypeName() << GetName() << "[" << link_path_ << "]" << endl;
}

SymbolLink::~SymbolLink()
{
}