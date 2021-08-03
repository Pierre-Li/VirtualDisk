#include "BaseCommand.h"

CommandDel::CommandDel()
{
}

//1、获取参数与路径
//2、对多个路径逐一操作
//3、判断通配符并进行匹配，删除匹配的文件
//4、路径指向目录时，删除目录下所有文件 
//5、路径指向文件时，/s 递归删除目录与子目录对应名字的文件；路径指向链接文件时，删除链接文件
bool CommandDel::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	int wild_flag = 0;
	int arg_flag = 0;
	GetArgAndPath(input_path_list, arg_list, path_list);
	for (auto it : path_list)
	{
		DealStrPath(it, deal_path_list, cur_path);
		Component* match_node;
		Component* match_node_sym;
		list<Component *> wild_file;
		match_node = cur_path->ContainWildPath(deal_path_list, wild_file, wild_flag);
		if (match_node == nullptr)
		{
			cout << "找不到对应路径" << endl;
			return false;
		}
		if (match_node->GetType() == TYPE_LINK_FILE || match_node->GetType() == TYPE_LINK_FOLDER)
		{
			//链接文件指向路径被删除
			DelComponent(match_node, arg_flag);
			return true;
		}
		deal_path_list.push_front("c:");
		match_node_sym = cur_path->ContainNodeIsSym(deal_path_list);//链接文件节点
		if (arg_list.size() == 0)
		{//无参数
			arg_flag = 0;
		}
		else if (arg_list.front() == "/s" && arg_list.size() == 1)
		{// 有参数 s
			arg_flag = 1;
		}
		else
		{
			cout << "请输入正确参数" << endl;
			return false;
		}
		if (wild_flag == 1)
		{//含通配符	
			Folder* com_folder = static_cast<Folder *>(match_node);
			for (auto it_com : wild_file)
			{
				DelComponent(it_com, arg_flag);
			}
			continue;
		}
		else
		{//不含通配符
			if (match_node->GetType() == TYPE_FOLDER)
			{//删除文件夹中所有文件
				Folder* folder = static_cast<Folder *>(match_node);
				list<string> file;
				for (auto it : folder->cmap_)
				{
					if (it.second->GetType() == TYPE_FILE)
					{
						file.push_back(it.first);
					}
				}
				for (auto it_file : file)
				{
					folder->Remove(it_file);
				}
				continue;
			}
			if (match_node->GetType() == TYPE_FILE && match_node_sym->GetType() != TYPE_LINK_FILE)
			{//删除文件
				DelComponent(match_node, arg_flag);
				continue;
			}
			if (match_node_sym->GetType() == TYPE_LINK_FILE)
			{//删除链接文件
				cout << "链接文件节点" << endl;
				DelComponent(match_node, arg_flag);
				DelComponent(match_node_sym, arg_flag);
				continue;
			}
		}
	}
	return true;
}	

void CommandDel::DelComponent(Component* node, int arg_flag)
{
	if (arg_flag)
	{
		string file_name = node->GetName();
		Component* father_node = node->GetFaterNode();
		deque<Component*> que_com;
		que_com.push_back(father_node);
		while (que_com.size())
		{
			Component *tem = que_com.front();
			que_com.pop_front();
			if (tem->GetType() == TYPE_FOLDER && tem->GetName() != "."  && tem->GetName() != "..")
			{
				Folder* folder = static_cast<Folder *>(tem);
				for (auto it : folder->cmap_)
				{
					if (it.second->GetType() == TYPE_FOLDER)
					{
						que_com.push_back(it.second);
					}
				}
				folder->Remove(file_name);
			}
		}
	}
	else
	{
		Component *father_node = node->GetFaterNode();
		father_node->Remove(node->GetName());
	}
}

CommandDel::~CommandDel()
{
}