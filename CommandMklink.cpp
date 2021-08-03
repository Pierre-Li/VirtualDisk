#include "BaseCommand.h"


CommandMklink::CommandMklink()
{
}

//1���ֱ�������·��
//2���жϣ�·��1Ϊ�Ǵ���·���Ҹ��ڵ�Ϊ����·����·��2Ϊ����·��
//3�����������ļ��������ļ����ļ���
bool CommandMklink::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list1, deal_path_list2;
	GetArgAndPath(input_path_list, arg_list, path_list);
	if (path_list.size() != 2)
	{
		cout << "·����ʽ����" << endl;
		return false;
	}
	DealStrPath(path_list.front(), deal_path_list1, cur_path);
	DealStrPath(path_list.back(), deal_path_list2, cur_path);
	Component *match_node1 = cur_path->ContainNode(deal_path_list1);//·��1ƥ��Ľڵ�
	Component *match_node2 = cur_path->ContainNode(deal_path_list2);//·��2ƥ��Ľڵ�
	if (match_node1 != nullptr)
	{
		cout << "�ܾ�����" << endl;
		return false;
	}
	if (match_node2 == nullptr)
	{
		cout << "�Ҳ���·��" << endl;
		return false;
	}
	deal_path_list1.push_front("c:");
	string sym_name = deal_path_list1.back();
	deal_path_list1.pop_back();
	match_node1 = cur_path->ContainNode(deal_path_list1);
	if (match_node1 == nullptr || match_node1->GetType() != TYPE_FOLDER)
	{
		cout << "·����ʽ����" << endl;
		return false;
	}
	if (match_node2->GetType() == TYPE_FOLDER)
	{
		match_node1->Add(sym_name, TYPE_LINK_FOLDER);
	}
	else if (match_node2->GetType() == TYPE_FILE)
	{
		match_node1->Add(sym_name, TYPE_LINK_FILE);
	}
	SymbolLink* sym = static_cast<SymbolLink*>(match_node1->GetNodeByName(sym_name));
	string link_path = "c:";
	for (auto it : deal_path_list2)
	{
		link_path += "\\" + it;
	}
	sym->SetLink(link_path);
	return true;
}

CommandMklink::~CommandMklink()
{
}