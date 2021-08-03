#include "BaseCommand.h"


CommandSave::CommandSave()
{
}

//1、处理路径。
//2、广度优先遍历获取磁盘目录.
//3、写入类型、名称、时间、folder_size、file_conent,link_path
bool CommandSave::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() == 0)
	{
		cout << "路径格式错误" << endl;
		return false;
	}
	if (!TrueDiskOper::IsTrueDiskPath(path_list.front()))
	{
		cout << "路径格式错误" << endl;
		return false;
	}
	string true_path;
	true_path = path_list.front();
	ofstream save_file(true_path.c_str());
	if (save_file.fail())
	{
		cout << "找不到对应文件" << endl;
		return false;
	}
	DeleteFile(true_path.c_str());
	//广度优先遍历获取磁盘目录
	deque<Component*> que_com;
	que_com.push_back(cur_path->GetRootNode());
	while (que_com.size())
	{
		Component *tem = que_com.front();
		que_com.pop_front();
		if (tem->GetType() == TYPE_FOLDER && tem->GetName() != "."  && tem->GetName() != "..")
		{
			Folder* folder = static_cast<Folder*>(tem);
			for (auto it:folder->cmap_)
			{
				que_com.push_back(it.second);
			}
		}
		TrueDiskOper::WriteDataToTrueDisk(true_path, tem);
	}
	return true;
}

CommandSave::~CommandSave()
{
}

