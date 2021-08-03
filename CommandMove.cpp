#include "BaseCommand.h"

CommandMove::CommandMove()
{
}

//1���������������·�������
//2���޲���ʱȡ������ͬ���ļ����У����в���ʱ����ͬ���ļ����У�
bool CommandMove::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
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
	Component *match_node2 = cur_path->ContainNode(deal_path_list2);//·��2ƥ��Ľڵ�;
	if (match_node1 == nullptr || match_node2 == nullptr)
	{
		cout << "�Ҳ�����Ӧ·��" << endl;
		return false;
	}
	if (cur_path->ListContain(match_node1,cur_path))
	{
		cout << "�����޷�����" << endl;
		return false;
	}
	if (ContainPath(match_node1,match_node2) || match_node2 == match_node1)
	{
		cout << "�ܾ�����" << endl;
		return false;
	}
	int flag = 0;
	if (arg_list.size() == 0)
	{
		//ȡ������
		flag = 0;
		if (match_node1->GetType() == TYPE_FOLDER && match_node2->GetType() == TYPE_FOLDER)
		{
			ComponentMove(match_node1, match_node2, flag);
			return true;
		}
		else if (match_node1->GetType() == TYPE_FILE && match_node2->GetType() == TYPE_FOLDER)
		{
			//�ļ��ƶ�
			ComponentMove(match_node1, match_node2, flag);
			return true;
		}
		else
		{
			cout << "·������" << endl;
			return false;
		}
	}
	else if (arg_list.size()==1 && arg_list.front() == "/y")
	{
		flag = 1;
		if (match_node1->GetType() == TYPE_FOLDER && match_node2->GetType() == TYPE_FOLDER)
		{
			ComponentMove(match_node1, match_node2, flag);
			return true;
		}
		if (match_node1->GetType() == TYPE_FILE && match_node2->GetType() == TYPE_FOLDER)
		{
			ComponentMove(match_node1, match_node2, flag);
			return true;
		}
		else
		{
			cout << "·������" << endl;
			return false;
		}
	}
	else
	{
		cout << "��������" << endl;
		return false;
	}
}

void CommandMove::ComponentMove(Component* node1, Component* node2,int flag)
{
	if (node1->GetFaterNode() == nullptr)
	{
		cout << "��Ŀ¼" << endl;
		return;
	}
	if (flag)
	{
		if (node2->GetNodeByName(node1->GetName()) != nullptr)
		{
			cout << "������ͬ�ļ� - ����" << endl;
			node2->Remove(node1->GetName());
		}
		Folder *node1_father = static_cast<Folder *>(node1->GetFaterNode());
		Folder* node2_folder = static_cast<Folder *>(node2);
		node2_folder->cmap_.insert(pair<string, Component*>(node1->GetName(), node1));
		node1_father->cmap_.erase(node1->GetName());
		node1->SetFatherNode(node2);
	}
	else
	{
		if (node2->GetNodeByName(node1->GetName()) != nullptr)
		{
			cout << "������ͬ�ļ� - ȡ���ƶ�" << endl;
			return;
		}
		Folder *node1_father = static_cast<Folder *>(node1->GetFaterNode());
		Folder* node2_folder = static_cast<Folder *>(node2);
		node2_folder->cmap_.insert(pair<string, Component*>(node1->GetName(), node1));
		node1_father->cmap_.erase(node1->GetName());
		node1->SetFatherNode(node2);
	}
}

bool CommandMove::ContainPath(Component* node1, Component* node2)
{
	while (node2 != nullptr)
	{
		node2 = node2->GetFaterNode();
		if (node2 == node1)
		{
			return true;
		}
	}
	return false;
}

CommandMove::~CommandMove()
{
}