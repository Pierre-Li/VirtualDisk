#include "VirtualDisk.h"

VirtualDisk* VirtualDisk::instance = nullptr;
VirtualDisk::Garbo VirtualDisk::garbo;

VirtualDisk::VirtualDisk()
{
	filedisk = new FileDisk();
	diskpath = new DiskPath();
	factory = new Factory();
	diskpath->SetListHead(filedisk->GetRootNode(), filedisk->GetRootNode()->GetName());
}

//单例对象
VirtualDisk* VirtualDisk::Instance()
{
	if (instance == nullptr)
	{
		instance = new VirtualDisk();
	}
	return instance;
}

//获得输入命令字符串
void VirtualDisk::GetCmdStr()
{
	cout << GetCurPath() << ">";
	string input_str;
	while (getline(cin, input_str))
	{
		if (input_str == "exit")
		{
			return;
		}
		if (input_str.size() != 0)
		{
			ExecuteCmd(input_str);
		}
		cout << endl;
		cout << GetCurPath() << ">";
	}
}

//获得当前路径
string VirtualDisk::GetCurPath()
{
	string w_cur_path = diskpath->GetCurPath();
	string cur_path = w_cur_path;
	return cur_path;
}

bool VirtualDisk::ExecuteCmd(string input_str)
{
	list<string> input_list_str;
	SplitInput(input_str, input_list_str); //切割为字符串列表
	string front_str = input_list_str.front();
	if (input_list_str.size() != 0)
	{
		input_list_str.pop_front();
	}
	transform(front_str.begin(), front_str.end(),front_str.begin(),::tolower);//命令转换小写
	BaseCommand* command = nullptr;
	command = factory->CreateCommand(front_str);
	if (command != nullptr)
	{
		command->ExecuteCmd(diskpath, input_list_str, filedisk);
		delete command;
	}
	return true;
}

//将输入字符串分割为列表,控制空格
void VirtualDisk::SplitInput(const string input_str, list<string>& input_list_str)
{
	string tmp_str;
	bool flag = false;
	for (unsigned int i = 0; i < input_str.size(); i++)
	{
		if (input_str[i] == ' ' && !flag )
		{
			flag = false;
			if (tmp_str != "")
			{
				input_list_str.push_back(tmp_str);
			}
			tmp_str = "";
			continue;
		}
		if (input_str[i] == '"')
		{
			if (!flag)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			continue;
		}
		if (input_str[i] == '/' || input_str[i] == '\\')
		{
			flag = false;
		}
		tmp_str += input_str[i];
	}
	if (tmp_str != "")
	{
		input_list_str.push_back(tmp_str);
	}
	
}

VirtualDisk::~VirtualDisk()
{
	delete filedisk;
	delete diskpath;
	delete factory;
}