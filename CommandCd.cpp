#include "BaseCommand.h"


CommandCd::CommandCd()
{
}

//����·�����´����б�
bool CommandCd::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	Component* com;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	com = cur_path->ContainNode(deal_path_list);
	if (com == nullptr)
	{
		cout << "·������" << endl;
		return false;
	}
	if (com->GetType() != TYPE_FOLDER)
	{
		cout << "�����ʽ����" << endl;
		return false;
	}
	if (arg_list.size() == 0)
	{
		cur_path->UpdateCurPath(deal_path_list); //���µ�ǰ·��
		return true;
	}
	else
	{
		cout << "��������" << endl;
	}
	return true;
}

CommandCd::~CommandCd()
{
}