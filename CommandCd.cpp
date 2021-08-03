#include "BaseCommand.h"


CommandCd::CommandCd()
{
}

//根据路径更新磁盘列表
bool CommandCd::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	Component* com;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	com = cur_path->ContainNode(deal_path_list);
	if (com == nullptr)
	{
		cout << "路径错误" << endl;
		return false;
	}
	if (com->GetType() != TYPE_FOLDER)
	{
		cout << "命令格式错误" << endl;
		return false;
	}
	if (arg_list.size() == 0)
	{
		cur_path->UpdateCurPath(deal_path_list); //更新当前路径
		return true;
	}
	else
	{
		cout << "参数错误" << endl;
	}
	return true;
}

CommandCd::~CommandCd()
{
}