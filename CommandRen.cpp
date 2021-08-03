#include "BaseCommand.h"

CommandRen::CommandRen()
{
}

bool CommandRen::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list1, deal_path_list2;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() != 2 )
	{
		cout << "命令格式不正确" << endl;
		return false;
	}
	string new_name = path_list.back();
	if (!NameIsLegal(new_name))
	{
		cout << "重命名不合法" << endl;
		return false;
	}
	DealStrPath(path_list.front(), deal_path_list1, cur_path);
	Component* match_node = cur_path->ContainNode(deal_path_list1);
	if (match_node == nullptr)
	{
		cout << "找不到路径" << endl;
		return false;
	}
	if (match_node->GetFaterNode() == nullptr)
	{
		cout << "根节点" << endl;
		return false;
	}
	if (cur_path->ListContain(match_node, cur_path))
	{
		cout << "进程无法访问" << endl;
		return false;
	}
	Folder* father_node = static_cast<Folder *>(match_node->GetFaterNode());
	if (father_node->GetNodeByName(new_name) != nullptr)
	{
		cout << "存在同名文件" << endl;
		return false;
	}
	match_node->SetName(new_name);
	father_node->cmap_.insert(pair<string, Component*>(match_node->GetName(), match_node));
	father_node->cmap_.erase(deal_path_list1.back());
	return true;
}

bool CommandRen::NameIsLegal(string new_name)
{
	for (unsigned int i = 0; i < new_name.size(); i++)
	{
		if (new_name[i] == '/' || new_name[i] == '\\' || new_name[i] == ':' || new_name[i] == '*' || new_name[i] == '?')
		{
			return false;
		}
	}
	return true;
}

CommandRen::~CommandRen()
{
}