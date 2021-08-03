#include "BaseCommand.h"


CommandCls::CommandCls()
{
}

bool CommandCls::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	system("cls");
	return true;
}

CommandCls::~CommandCls()
{
}