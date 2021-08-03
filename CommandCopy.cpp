#include "BaseCommand.h"

CommandCopy::CommandCopy()
{
}

//1、分割参数和路径
//2、copy路径为真实路径时，文件夹;获取文件夹下所有文件；文件;直接读文件数据
//3、copy路径为虚拟磁盘时，判断是否含有通配符 含通配符：匹配对应文件进行copy，不含通配符：文件夹;获取文件夹下所有文件；文件;copy文件
bool CommandCopy::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list1, deal_path_list2;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() != 2)
	{
		cout << "命令格式不正确" << endl;
		return false;
	}
	Component* match_node1;
	Component* match_node2;
	string path1, path2, file_name;
	path1 = path_list.front();
	path2 = path_list.back();
	if (TrueDiskOper::IsTrueDiskPath(path1))
	{
		//真实路径拷贝
		if (path1.size() == 0)
		{
			cout << "找不到对应文件" << endl;
			return false;
		}
		DealStrPath(path2, deal_path_list2, cur_path);
		match_node2 = cur_path->ContainNode(deal_path_list2);
		if (match_node2 == nullptr)
		{
			cout << "找不到路径" << endl;
			return false;
		}
		if (match_node2->GetType() != TYPE_FOLDER)
		{
			cout << "路径格式错误" << endl;
			return false;
		}
		if (TrueDiskOper::IsFileOrFolder(path1, file_name))
		{
			//文件类型
			ifstream read_file(path1, ios::binary);
			if (read_file.fail())
			{
				cout << "找不到对应文件" << endl;
				return false;
			}
			read_file.close();
			TrueFileCopy(path1, file_name, match_node2);
			return true;
		}
		else
		{
			//文件夹类型
			vector<string> filesname;
			TrueDiskOper::GetFilsName(path1, filesname);
			for (auto it : filesname)
			{
				string file_path;
				file_path = path1 + "\\" + it;
				ifstream read_file(file_path, ios::binary);
				if (read_file.fail())
				{
					cout << it << "文件打开失败" << endl;
					continue;
				}
				read_file.close();
				TrueFileCopy(file_path, it, match_node2);
			}
			return true;
		}
	}
	else
	{
		//虚拟路径拷贝
		DealStrPath(path1, deal_path_list1, cur_path);
		DealStrPath(path2, deal_path_list2, cur_path);
		list<Component *> wild_file;
		int flag =0;
		match_node1 = cur_path->ContainWildPath(deal_path_list1, wild_file, flag);
		match_node2 = cur_path->ContainNode(deal_path_list2);
		if (match_node1 == nullptr || match_node2 == nullptr)
		{
			cout << "找不到路径" << endl;
			return false;
		}
		if (flag == 1)
		{
			//含通配符
			if (match_node2->GetType() == TYPE_FOLDER)
			{
				for (auto it : wild_file)
				{
					FileCopy(it, match_node2);
				}
				return true;
			}
			else
			{
				cout << "路径格式错误" << endl;
				return false;
			}
		}
		//不含通配符
		if (match_node1->GetType() == TYPE_FILE && match_node2->GetType() == TYPE_FOLDER)
		{
			//文件类型
			FileCopy(match_node1, match_node2);
			return true;
		}
		else if (match_node1->GetType() == TYPE_FOLDER && match_node2->GetType() == TYPE_FOLDER)
		{
			//文件夹类型
			FolderCopy(match_node1, match_node2);
			return true;
		}
		else
		{
			cout << "路径错误" << endl;
			return false;
		}
	}
	return true;
}

void CommandCopy::FileCopy(Component* file, Component* path_node)
{
	int num;
	Folder* folder_node = static_cast<Folder *>(path_node);
	File * fil_node = static_cast<File *>(file);
	string file_name = file->GetName();
	vector<unsigned char> f1_conent = fil_node->GetContent(num);
	if (folder_node->GetNodeByName(file_name) != nullptr)
	{
		cout << "存在同名文件" << endl;
		return;
	}
	folder_node->Add(file_name, TYPE_FILE);
	File* copy_file = static_cast<File *>(folder_node->GetNodeByName(file_name));
	copy_file->WriteContent(f1_conent, num);

}

void CommandCopy::FolderCopy(Component* path_node1, Component* path_node2)
{
	Folder* folder_node1 = static_cast<Folder *>(path_node1);
	Folder* folder_node2 = static_cast<Folder *>(path_node2);
	vector<string> files_name;
	for (auto it : folder_node1->cmap_)
	{
		if (it.second->GetType() == TYPE_FILE)
		{
			files_name.push_back(it.second->GetName());
		}
	}
	for (auto it : files_name) //按文件名拷贝
	{
		vector<unsigned char> file_conent;
		if (folder_node2->GetNodeByName(it) != nullptr)
		{
			cout << "存在同名文件" << it << endl;
			continue;
		}
		File *fil_node = static_cast<File *>(folder_node1->GetNodeByName(it));
		FileCopy(fil_node, folder_node2);
	}
}

void CommandCopy::TrueFileCopy(string true_path, string file_name, Component* path_node)
{
	Folder* folder_node = static_cast<Folder *>(path_node);
	if (folder_node->GetNodeByName(file_name) != nullptr)
	{
		cout << "存在同名文件" << endl;
		return;
	}
	folder_node->Add(file_name, TYPE_FILE);
	File* file = static_cast<File *>(folder_node->GetNodeByName(file_name));
	file->WriteContent(TrueDiskOper::ReadFileFromTrueDisk(true_path), TrueDiskOper::ReadFileFromTrueDisk(true_path).capacity());
	return;
}

CommandCopy::~CommandCopy()
{
}