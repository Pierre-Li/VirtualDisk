#include "BaseCommand.h"

BaseCommand::BaseCommand()
{
}

//获得输入参数和路径
void BaseCommand::GetArgAndPath(list<string> arg_path_list, list<string>&arg_list, list<string>&path_list)
{
	arg_list.clear();
	path_list.clear();
	for (auto it : arg_path_list)
	{
		if (it[0] == '/' && it.size() >= 2 && it.size() <= 3)
		{
			arg_list.push_back(it);
		}
		else
		{
			path_list.push_back(it);
		}
	}
}

//处理列表路径，相对路径转绝对路径
void BaseCommand::DealListPath(list<string> input_path, list<string>& deal_path, DiskPath* diskpath)
{
	deal_path.clear();
	if (input_path.size() == 0)
	{
		deal_path = diskpath->GetListCurPath();
	}
	else
	{
		string tem, str;
		tem = input_path.front();
		DealStrPath(tem, deal_path, diskpath);
	}
}

//处理字符串路径，相对路径转绝对路径
void BaseCommand::DealStrPath(const string& input_path, list<string>& deal_path, DiskPath* diskpath)
{
	deal_path.clear();
	if (input_path.size() == 0)
	{
		deal_path = diskpath->GetListCurPath();
	}
	else
	{
		string str;
		for (unsigned int i = 0; i < input_path.size(); i++)
		{
			if (i == 0 && input_path[0] == '\\')
			{
				deal_path.push_back("C:");
				continue;
			}
			if (str == "." && i == 0)
			{
				deal_path.splice(deal_path.end(), diskpath->GetListCurPath());
				continue;
			}
			if (input_path[i] == '\\' || input_path[i] == '/')
			{
				if (str == "")
				{
					continue;
				}
				deal_path.push_back(str);
				str = "";
				continue;
			}
			str += input_path[i];
		}
		if (str != "")
		{
			deal_path.push_back(str);
		}
		list<string>::iterator it = find(deal_path.begin(), deal_path.end(), "C:");
		list<string>::iterator it1 = find(deal_path.begin(), deal_path.end(), "c:");
		if (it == deal_path.end() && it1 == deal_path.end())
		{
			deal_path.splice(deal_path.begin(), diskpath->GetListCurPath());
		}
	}
}


BaseCommand::~BaseCommand()
{
}