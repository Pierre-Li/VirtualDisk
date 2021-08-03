#include "BaseCommand.h"


CommandDir::CommandDir()
{
}

//1����ȡ���������·��������·�����д���
//2�����ݲ�ͬ������ʾ��Ӧ�ļ�
bool CommandDir::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	Component* match_node;
	match_node = cur_path->ContainNode(deal_path_list);
	if (match_node == nullptr)
	{
		cout << "�Ҳ����ļ�·��" << endl;
		return false;
	}
	if (match_node->GetType() != TYPE_FOLDER)
	{
		cout << "·����ʽ����" << endl;
		return false;
	}
	Folder* folder_node = static_cast<Folder*> (match_node);
	if (arg_list.size() == 0)
	{
		//���Ŀ¼�е��ļ�����Ŀ¼
		folder_node->DisplayAll();//��ʾ
		return true;
	}
	else if (arg_list.size() == 1 && arg_list.front() == "/ad")
	{
		folder_node->DisplayFolder();//��ʾ
	}
	else if (arg_list.size() == 1 && arg_list.front() == "/s")
	{
		folder_node->DisplayFile();//��ʾ
	}
	else
	{
		cout << "��������" << endl;
		return false;
	}
	return true;
}

CommandDir::~CommandDir()
{
}