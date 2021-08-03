#include "BaseCommand.h"


CommandDir::CommandDir()
{
}

//1、获取输入参数和路径，并对路径进行处理
//2、根据不同参数显示对应文件
bool CommandDir::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	Component* match_node;
	match_node = cur_path->ContainNode(deal_path_list);
	if (match_node == nullptr)
	{
		cout << "找不到文件路径" << endl;
		return false;
	}
	if (match_node->GetType() != TYPE_FOLDER)
	{
		cout << "路径格式错误" << endl;
		return false;
	}
	Folder* folder_node = static_cast<Folder*> (match_node);
	if (arg_list.size() == 0)
	{
		//输出目录中的文件和子目录
		folder_node->DisplayAll();//显示
		return true;
	}
	else if (arg_list.size() == 1 && arg_list.front() == "/ad")
	{
		folder_node->DisplayFolder();//显示
	}
	else if (arg_list.size() == 1 && arg_list.front() == "/s")
	{
		folder_node->DisplayFile();//显示
	}
	else
	{
		cout << "参数错误" << endl;
		return false;
	}
	return true;
}

CommandDir::~CommandDir()
{
}