#include "BaseCommand.h"

CommandRd::CommandRd()
{
}

//1、获取参数和路径
//2、无参数时，删除当前路径时进程冲突，文件非空不能删除,链接文件删除链接节点
//3、参数为/s时，进程冲突情况下，可以删除，当前路径跳转为根节点
//4、参数为/s时，可以对非空文件进行删除
bool CommandRd::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	Component* match_node = cur_path->ContainNode(deal_path_list);
	if (match_node == nullptr)
	{
		cout << "找不到指定路径" << endl;
		return false;
	}
	if (match_node->GetType() != TYPE_FOLDER)
	{
		cout << "命令格式错误" << endl;
		return false;
	}
	deal_path_list.push_front("c:");
	Component* match_sym_node = cur_path->ContainNodeIsSym(deal_path_list);//判断最终路径节点是否为链接文件
	int flag = 0;
	if (arg_list.size() == 0)
	{
		flag = 0;
		if (cur_path->ListContain(match_node, cur_path) || cur_path->ListContain(match_sym_node, cur_path))
		{
			cout << "进程无法访问" << endl;
			return false;
		}
		if (match_sym_node->GetType() == TYPE_LINK_FOLDER)
		{
			LinkRemove(match_node, match_sym_node, flag);
			return true;
		}
		ComponentRemove(match_node, flag);
		return true;
	}
	else if (arg_list.size() == 1 && arg_list.front() == "/s")
	{
		flag = 1;
		if (cur_path->ListContain(match_node, cur_path) || cur_path->ListContain(match_sym_node, cur_path))
		{
			cout << "删除当前进程文件" << endl;
			if (match_node->GetFaterNode() == nullptr)
			{
				//删除磁盘全部文件
				file_disk->FormatDisk();
				cur_path->ClearDiskPath();
				cur_path->SetListHead(file_disk->GetRootNode(), file_disk->GetRootNode()->GetName());
				return true;
			}
			else
			{
				if (match_sym_node->GetType() == TYPE_LINK_FOLDER)
				{
					cur_path->SetListHead(cur_path->GetRootNode(), cur_path->GetRootNode()->GetName());
					LinkRemove(match_node, match_sym_node, flag);
					return true;
				}
				cur_path->SetListHead(cur_path->GetRootNode(), cur_path->GetRootNode()->GetName());
				ComponentRemove(match_node, flag);
				return true;
			}
		}
		else 
		{
			if (match_sym_node->GetType() == TYPE_LINK_FOLDER)
			{
				LinkRemove(match_node, match_sym_node, flag);
				return true;
			}
			ComponentRemove(match_node, flag);
			return true;
		}
	}
	else
	{
		cout << "参数错误" << endl;
		return false;
	}
}

void CommandRd::ComponentRemove(Component* node, int flag)
{
	if (flag)
	{
		Folder* father_node = static_cast<Folder*>(node->GetFaterNode());
		cout << "删除非空文件夹" << endl;
		father_node->Remove(node->GetName());
	}
	else
	{
		if (node->GetFaterNode() == nullptr)
		{
			cout << "根目录" << endl;
			return;
		}
		Folder*  folder_node= static_cast<Folder*>(node);
		Component *father_node = node->GetFaterNode();
		if (folder_node->cmap_.size() != 0)
		{
			cout << "文件夹非空" << endl;
			return;
		}
		father_node->Remove(node->GetName());
	}
}

void CommandRd::LinkRemove( Component* node1, Component* node2, int flag)
{
	cout << "链接文件节点" << endl;
	if (node1->GetFaterNode() == nullptr)
	{
		cout << "根目录" << endl;
		return;
	}
	Component* father_node1 = node1->GetFaterNode();
	Folder* folder_node1 = static_cast<Folder*>(node1);
	Component* father_node2 = node2->GetFaterNode();
	if (flag)
	{
		father_node1->Remove(node1->GetName());
		father_node2->Remove(node2->GetName());
	}
	else
	{
		if (folder_node1->cmap_.size() != 0)
		{
			cout << "文件夹非空" << endl;
			return;
		}
		father_node1->Remove(node1->GetName());
		father_node2->Remove(node2->GetName());
	}
}

CommandRd::~CommandRd()
{
}