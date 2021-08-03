#include "BaseCommand.h"

CommandRd::CommandRd()
{
}

//1����ȡ������·��
//2���޲���ʱ��ɾ����ǰ·��ʱ���̳�ͻ���ļ��ǿղ���ɾ��,�����ļ�ɾ�����ӽڵ�
//3������Ϊ/sʱ�����̳�ͻ����£�����ɾ������ǰ·����תΪ���ڵ�
//4������Ϊ/sʱ�����ԶԷǿ��ļ�����ɾ��
bool CommandRd::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	GetArgAndPath(input_path_list, arg_list, path_list);
	DealListPath(path_list, deal_path_list, cur_path);
	Component* match_node = cur_path->ContainNode(deal_path_list);
	if (match_node == nullptr)
	{
		cout << "�Ҳ���ָ��·��" << endl;
		return false;
	}
	if (match_node->GetType() != TYPE_FOLDER)
	{
		cout << "�����ʽ����" << endl;
		return false;
	}
	deal_path_list.push_front("c:");
	Component* match_sym_node = cur_path->ContainNodeIsSym(deal_path_list);//�ж�����·���ڵ��Ƿ�Ϊ�����ļ�
	int flag = 0;
	if (arg_list.size() == 0)
	{
		flag = 0;
		if (cur_path->ListContain(match_node, cur_path) || cur_path->ListContain(match_sym_node, cur_path))
		{
			cout << "�����޷�����" << endl;
			return false;
		}
		if (match_sym_node->GetType() == TYPE_LINK_FOLDER)
		{
			LinkRemove(match_node, match_sym_node, flag);
			return true;
		}
		ComponentRemove(match_node, flag);
		return true;
	}
	else if (arg_list.size() == 1 && arg_list.front() == "/s")
	{
		flag = 1;
		if (cur_path->ListContain(match_node, cur_path) || cur_path->ListContain(match_sym_node, cur_path))
		{
			cout << "ɾ����ǰ�����ļ�" << endl;
			if (match_node->GetFaterNode() == nullptr)
			{
				//ɾ������ȫ���ļ�
				file_disk->FormatDisk();
				cur_path->ClearDiskPath();
				cur_path->SetListHead(file_disk->GetRootNode(), file_disk->GetRootNode()->GetName());
				return true;
			}
			else
			{
				if (match_sym_node->GetType() == TYPE_LINK_FOLDER)
				{
					cur_path->SetListHead(cur_path->GetRootNode(), cur_path->GetRootNode()->GetName());
					LinkRemove(match_node, match_sym_node, flag);
					return true;
				}
				cur_path->SetListHead(cur_path->GetRootNode(), cur_path->GetRootNode()->GetName());
				ComponentRemove(match_node, flag);
				return true;
			}
		}
		else 
		{
			if (match_sym_node->GetType() == TYPE_LINK_FOLDER)
			{
				LinkRemove(match_node, match_sym_node, flag);
				return true;
			}
			ComponentRemove(match_node, flag);
			return true;
		}
	}
	else
	{
		cout << "��������" << endl;
		return false;
	}
}

void CommandRd::ComponentRemove(Component* node, int flag)
{
	if (flag)
	{
		Folder* father_node = static_cast<Folder*>(node->GetFaterNode());
		cout << "ɾ���ǿ��ļ���" << endl;
		father_node->Remove(node->GetName());
	}
	else
	{
		if (node->GetFaterNode() == nullptr)
		{
			cout << "��Ŀ¼" << endl;
			return;
		}
		Folder*  folder_node= static_cast<Folder*>(node);
		Component *father_node = node->GetFaterNode();
		if (folder_node->cmap_.size() != 0)
		{
			cout << "�ļ��зǿ�" << endl;
			return;
		}
		father_node->Remove(node->GetName());
	}
}

void CommandRd::LinkRemove( Component* node1, Component* node2, int flag)
{
	cout << "�����ļ��ڵ�" << endl;
	if (node1->GetFaterNode() == nullptr)
	{
		cout << "��Ŀ¼" << endl;
		return;
	}
	Component* father_node1 = node1->GetFaterNode();
	Folder* folder_node1 = static_cast<Folder*>(node1);
	Component* father_node2 = node2->GetFaterNode();
	if (flag)
	{
		father_node1->Remove(node1->GetName());
		father_node2->Remove(node2->GetName());
	}
	else
	{
		if (folder_node1->cmap_.size() != 0)
		{
			cout << "�ļ��зǿ�" << endl;
			return;
		}
		father_node1->Remove(node1->GetName());
		father_node2->Remove(node2->GetName());
	}
}

CommandRd::~CommandRd()
{
}