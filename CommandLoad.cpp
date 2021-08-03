#include "BaseCommand.h"

CommandLoad::CommandLoad()
{
}

//1、处理路径。
//2、读文件，获取根节点。
//3、广度优先遍历创建树形磁盘目录
//4、设置根节点
bool CommandLoad::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() == 0)
	{
		cout << "路径错误" << endl;
		return false;
	}
	if (!TrueDiskOper::IsTrueDiskPath(path_list.front())) //判断真实路径
	{
		cout << "路径格式错误" << endl;
		return false;
	}
	string path;
	path = path_list.front();
	ifstream load_file(path.c_str(), ios::binary);
	if (load_file.fail())
	{
		cout << "找不到对应文件" << endl;
		return false;
	}
	Component *tem_root = TrueDiskOper::ReadDataFromTrueDisk(load_file);//读文件输出根组件
	if (tem_root == nullptr)
	{
		cout << "文件内容错误" << endl;
		return false;
	}
	//广度优先遍历创建树形文件夹
	deque<Component *> que_com;
	que_com.push_back(tem_root);
	while (que_com.size())
	{
		Component *tem = que_com.front();
		que_com.pop_front();
		if (tem->GetType() == TYPE_FOLDER)
		{
			Folder* folder = static_cast<Folder*>(tem);
			for (int i = 1; i <= folder->GetSize(); i++)
			{
				Component* tmp_comp = TrueDiskOper::ReadDataFromTrueDisk(load_file);
				folder->cmap_.insert(std::pair<string, Component*>(tmp_comp->GetName(), tmp_comp));
				tmp_comp->SetFatherNode(tem);
				if (tmp_comp->GetType() == TYPE_FOLDER) 
					que_com.push_back(tmp_comp);
			}
		}
	}
	load_file.close();
	file_disk->FormatDisk();
	file_disk->SetRootNode(tem_root);
	cur_path->ClearDiskPath();
	cur_path->SetListHead(tem_root, tem_root->GetName());//设置根节点
	return true;
}

CommandLoad::~CommandLoad()
{
}