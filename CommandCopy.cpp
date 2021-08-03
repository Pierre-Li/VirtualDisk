#include "BaseCommand.h"

CommandCopy::CommandCopy()
{
}

//1���ָ������·��
//2��copy·��Ϊ��ʵ·��ʱ���ļ���;��ȡ�ļ����������ļ����ļ�;ֱ�Ӷ��ļ�����
//3��copy·��Ϊ�������ʱ���ж��Ƿ���ͨ��� ��ͨ�����ƥ���Ӧ�ļ�����copy������ͨ������ļ���;��ȡ�ļ����������ļ����ļ�;copy�ļ�
bool CommandCopy::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list1, deal_path_list2;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() != 2)
	{
		cout << "�����ʽ����ȷ" << endl;
		return false;
	}
	Component* match_node1;
	Component* match_node2;
	string path1, path2, file_name;
	path1 = path_list.front();
	path2 = path_list.back();
	if (TrueDiskOper::IsTrueDiskPath(path1))
	{
		//��ʵ·������
		if (path1.size() == 0)
		{
			cout << "�Ҳ�����Ӧ�ļ�" << endl;
			return false;
		}
		DealStrPath(path2, deal_path_list2, cur_path);
		match_node2 = cur_path->ContainNode(deal_path_list2);
		if (match_node2 == nullptr)
		{
			cout << "�Ҳ���·��" << endl;
			return false;
		}
		if (match_node2->GetType() != TYPE_FOLDER)
		{
			cout << "·����ʽ����" << endl;
			return false;
		}
		if (TrueDiskOper::IsFileOrFolder(path1, file_name))
		{
			//�ļ�����
			ifstream read_file(path1, ios::binary);
			if (read_file.fail())
			{
				cout << "�Ҳ�����Ӧ�ļ�" << endl;
				return false;
			}
			read_file.close();
			TrueFileCopy(path1, file_name, match_node2);
			return true;
		}
		else
		{
			//�ļ�������
			vector<string> filesname;
			TrueDiskOper::GetFilsName(path1, filesname);
			for (auto it : filesname)
			{
				string file_path;
				file_path = path1 + "\\" + it;
				ifstream read_file(file_path, ios::binary);
				if (read_file.fail())
				{
					cout << it << "�ļ���ʧ��" << endl;
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
		//����·������
		DealStrPath(path1, deal_path_list1, cur_path);
		DealStrPath(path2, deal_path_list2, cur_path);
		list<Component *> wild_file;
		int flag =0;
		match_node1 = cur_path->ContainWildPath(deal_path_list1, wild_file, flag);
		match_node2 = cur_path->ContainNode(deal_path_list2);
		if (match_node1 == nullptr || match_node2 == nullptr)
		{
			cout << "�Ҳ���·��" << endl;
			return false;
		}
		if (flag == 1)
		{
			//��ͨ���
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
				cout << "·����ʽ����" << endl;
				return false;
			}
		}
		//����ͨ���
		if (match_node1->GetType() == TYPE_FILE && match_node2->GetType() == TYPE_FOLDER)
		{
			//�ļ�����
			FileCopy(match_node1, match_node2);
			return true;
		}
		else if (match_node1->GetType() == TYPE_FOLDER && match_node2->GetType() == TYPE_FOLDER)
		{
			//�ļ�������
			FolderCopy(match_node1, match_node2);
			return true;
		}
		else
		{
			cout << "·������" << endl;
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
		cout << "����ͬ���ļ�" << endl;
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
	for (auto it : files_name) //���ļ�������
	{
		vector<unsigned char> file_conent;
		if (folder_node2->GetNodeByName(it) != nullptr)
		{
			cout << "����ͬ���ļ�" << it << endl;
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
		cout << "����ͬ���ļ�" << endl;
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