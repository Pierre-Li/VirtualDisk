#include "SymbolLink.h"

SymbolLink::SymbolLink(Component* _father_node, const string &_name, int _type) :Component(_father_node, _name, _type)
{

}

//设置链接文件的链接路径
void SymbolLink::SetLink(const string & new_path)
{
	link_path_ = new_path;
}

//获得字符串型链接文件指向的路径
string SymbolLink::GetLink()
{
	return link_path_;
}

//获得列表型链接文件指向的路径
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

//链接文件显示
void SymbolLink::Display()
{
	cout << setiosflags(ios::left) << GetTime() << "   " << left << setw(15) << GetTypeName() << GetName() << "[" << link_path_ << "]" << endl;
}

SymbolLink::~SymbolLink()
{
}