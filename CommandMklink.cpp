#include "BaseCommand.h"


CommandMklink::CommandMklink()
{
}

//1、分别处理两个路径
//2、判断：路径1为非磁盘路径且父节点为磁盘路径，路径2为磁盘路径
//3、创建链接文件，链接文件和文件夹
bool CommandMklink::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list1, deal_path_list2;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() != 2)
	{
		cout << "路径格式错误" << endl;
		return false;
	}
	DealStrPath(path_list.front(), deal_path_list1, cur_path);
	DealStrPath(path_list.back(), deal_path_list2, cur_path);
	Component *match_node1 = cur_path->ContainNode(deal_path_list1);//路径1匹配的节点
	Component *match_node2 = cur_path->ContainNode(deal_path_list2);//路径2匹配的节点
	if (match_node1 != nullptr)
	{
		cout << "拒绝访问" << endl;
		return false;
	}
	if (match_node2 == nullptr)
	{
		cout << "找不到路径" << endl;
		return false;
	}
	deal_path_list1.push_front("c:");
	string sym_name = deal_path_list1.back();
	deal_path_list1.pop_back();
	match_node1 = cur_path->ContainNode(deal_path_list1);
	if (match_node1 == nullptr || match_node1->GetType() != TYPE_FOLDER)
	{
		cout << "路径格式错误" << endl;
		return false;
	}
	if (match_node2->GetType() == TYPE_FOLDER)
	{
		match_node1->Add(sym_name, TYPE_LINK_FOLDER);
	}
	else if (match_node2->GetType() == TYPE_FILE)
	{
		match_node1->Add(sym_name, TYPE_LINK_FILE);
	}
	SymbolLink* sym = static_cast<SymbolLink*>(match_node1->GetNodeByName(sym_name));
	string link_path = "c:";
	for (auto it : deal_path_list2)
	{
		link_path += "\\" + it;
	}
	sym->SetLink(link_path);
	return true;
}

CommandMklink::~CommandMklink()
{
}