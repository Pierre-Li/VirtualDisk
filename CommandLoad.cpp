#include "BaseCommand.h"

CommandLoad::CommandLoad()
{
}

//1������·����
//2�����ļ�����ȡ���ڵ㡣
//3��������ȱ����������δ���Ŀ¼
//4�����ø��ڵ�
bool CommandLoad::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() == 0)
	{
		cout << "·������" << endl;
		return false;
	}
	if (!TrueDiskOper::IsTrueDiskPath(path_list.front())) //�ж���ʵ·��
	{
		cout << "·����ʽ����" << endl;
		return false;
	}
	string path;
	path = path_list.front();
	ifstream load_file(path.c_str(), ios::binary);
	if (load_file.fail())
	{
		cout << "�Ҳ�����Ӧ�ļ�" << endl;
		return false;
	}
	Component *tem_root = TrueDiskOper::ReadDataFromTrueDisk(load_file);//���ļ���������
	if (tem_root == nullptr)
	{
		cout << "�ļ����ݴ���" << endl;
		return false;
	}
	//������ȱ������������ļ���
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
	cur_path->SetListHead(tem_root, tem_root->GetName());//���ø��ڵ�
	return true;
}

CommandLoad::~CommandLoad()
{
}