#include "BaseCommand.h"


CommandMd::CommandMd()
{
}

//1����ȡ������·��
//2���ж�·���Ƿ���ڣ�����ʱ�������ѣ������ڰ�·�����д���
bool CommandMd::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	if (deal_path_list.size() == 0)
	{
		cout << "·������" << endl;
		return false;
	}
	if (cur_path->ContainNode(deal_path_list) != nullptr)
	{
		cout << "·������" << endl;
		return false;
	}
	else
	{
		//·�������ڣ���·������
		Component *cur_node;
		cur_node = cur_path->GetRootNode();
		for (auto it : deal_path_list)
		{
			if (it == "..")
			{
				cur_node = cur_node->GetFaterNode();
				continue;
			}
			if (it == ".")
			{
				continue;
			}
			if (cur_node->GetType() == TYPE_FOLDER)//��Ӧ�ļ���
			{ 
				Component* tem_com = cur_node->GetNodeByName(it);
				if (tem_com == nullptr)
				{
					cur_node->Add(it, TYPE_FOLDER);//�����ļ���
					cur_node->Add(".", TYPE_FOLDER);
					cur_node->Add("..", TYPE_FOLDER);
					tem_com = cur_node->GetNodeByName(it);
				}
				if (tem_com->GetType() == TYPE_LINK_FOLDER)
				{
					SymbolLink *sym_node = static_cast<SymbolLink *>(tem_com);
					list<string> list_sym = sym_node->GetListLinkpath();
					Component* com_sym = cur_path->ContainNode(list_sym);
					tem_com = com_sym;
				}
				cur_node = tem_com;
			}
			else //�ļ�����
			{
				cout << "·������" << endl;
				break;
			}
		}
		return true;
	}
}

CommandMd::~CommandMd()
{
}