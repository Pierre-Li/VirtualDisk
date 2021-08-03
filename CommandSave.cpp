#include "BaseCommand.h"


CommandSave::CommandSave()
{
}

//1������·����
//2��������ȱ�����ȡ����Ŀ¼.
//3��д�����͡����ơ�ʱ�䡢folder_size��file_conent,link_path
bool CommandSave::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() == 0)
	{
		cout << "·����ʽ����" << endl;
		return false;
	}
	if (!TrueDiskOper::IsTrueDiskPath(path_list.front()))
	{
		cout << "·����ʽ����" << endl;
		return false;
	}
	string true_path;
	true_path = path_list.front();
	ofstream save_file(true_path.c_str());
	if (save_file.fail())
	{
		cout << "�Ҳ�����Ӧ�ļ�" << endl;
		return false;
	}
	DeleteFile(true_path.c_str());
	//������ȱ�����ȡ����Ŀ¼
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

