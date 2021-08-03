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

//��������
VirtualDisk* VirtualDisk::Instance()
{
	if (instance == nullptr)
	{
		instance = new VirtualDisk();
	}
	return instance;
}

//������������ַ���
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

//��õ�ǰ·��
string VirtualDisk::GetCurPath()
{
	string w_cur_path = diskpath->GetCurPath();
	string cur_path = w_cur_path;
	return cur_path;
}

bool VirtualDisk::ExecuteCmd(string input_str)
{
	list<string> input_list_str;
	SplitInput(input_str, input_list_str); //�и�Ϊ�ַ����б�
	string front_str = input_list_str.front();
	if (input_list_str.size() != 0)
	{
		input_list_str.pop_front();
	}
	transform(front_str.begin(), front_str.end(),front_str.begin(),::tolower);//����ת��Сд
	BaseCommand* command = nullptr;
	command = factory->CreateCommand(front_str);
	if (command != nullptr)
	{
		command->ExecuteCmd(diskpath, input_list_str, filedisk);
		delete command;
	}
	return true;
}

//�������ַ����ָ�Ϊ�б�,���ƿո�
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