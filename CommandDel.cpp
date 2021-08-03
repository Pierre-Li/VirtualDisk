#include "BaseCommand.h"

CommandDel::CommandDel()
{
}

//1����ȡ������·��
//2���Զ��·����һ����
//3���ж�ͨ���������ƥ�䣬ɾ��ƥ����ļ�
//4��·��ָ��Ŀ¼ʱ��ɾ��Ŀ¼�������ļ� 
//5��·��ָ���ļ�ʱ��/s �ݹ�ɾ��Ŀ¼����Ŀ¼��Ӧ���ֵ��ļ���·��ָ�������ļ�ʱ��ɾ�������ļ�
bool CommandDel::ExecuteCmd(DiskPath* cur_path, list<string>& input_path_list, FileDisk* file_disk)
{
	list<string>arg_list, path_list, deal_path_list;
	int wild_flag = 0;
	int arg_flag = 0;
	GetArgAndPath(input_path_list, arg_list, path_list);
	for (auto it : path_list)
	{
		DealStrPath(it, deal_path_list, cur_path);
		Component* match_node;
		Component* match_node_sym;
		list<Component *> wild_file;
		match_node = cur_path->ContainWildPath(deal_path_list, wild_file, wild_flag);
		if (match_node == nullptr)
		{
			cout << "�Ҳ�����Ӧ·��" << endl;
			return false;
		}
		if (match_node->GetType() == TYPE_LINK_FILE || match_node->GetType() == TYPE_LINK_FOLDER)
		{
			//�����ļ�ָ��·����ɾ��
			DelComponent(match_node, arg_flag);
			return true;
		}
		deal_path_list.push_front("c:");
		match_node_sym = cur_path->ContainNodeIsSym(deal_path_list);//�����ļ��ڵ�
		if (arg_list.size() == 0)
		{//�޲���
			arg_flag = 0;
		}
		else if (arg_list.front() == "/s" && arg_list.size() == 1)
		{// �в��� s
			arg_flag = 1;
		}
		else
		{
			cout << "��������ȷ����" << endl;
			return false;
		}
		if (wild_flag == 1)
		{//��ͨ���	
			Folder* com_folder = static_cast<Folder *>(match_node);
			for (auto it_com : wild_file)
			{
				DelComponent(it_com, arg_flag);
			}
			continue;
		}
		else
		{//����ͨ���
			if (match_node->GetType() == TYPE_FOLDER)
			{//ɾ���ļ����������ļ�
				Folder* folder = static_cast<Folder *>(match_node);
				list<string> file;
				for (auto it : folder->cmap_)
				{
					if (it.second->GetType() == TYPE_FILE)
					{
						file.push_back(it.first);
					}
				}
				for (auto it_file : file)
				{
					folder->Remove(it_file);
				}
				continue;
			}
			if (match_node->GetType() == TYPE_FILE && match_node_sym->GetType() != TYPE_LINK_FILE)
			{//ɾ���ļ�
				DelComponent(match_node, arg_flag);
				continue;
			}
			if (match_node_sym->GetType() == TYPE_LINK_FILE)
			{//ɾ�������ļ�
				cout << "�����ļ��ڵ�" << endl;
				DelComponent(match_node, arg_flag);
				DelComponent(match_node_sym, arg_flag);
				continue;
			}
		}
	}
	return true;
}	

void CommandDel::DelComponent(Component* node, int arg_flag)
{
	if (arg_flag)
	{
		string file_name = node->GetName();
		Component* father_node = node->GetFaterNode();
		deque<Component*> que_com;
		que_com.push_back(father_node);
		while (que_com.size())
		{
			Component *tem = que_com.front();
			que_com.pop_front();
			if (tem->GetType() == TYPE_FOLDER && tem->GetName() != "."  && tem->GetName() != "..")
			{
				Folder* folder = static_cast<Folder *>(tem);
				for (auto it : folder->cmap_)
				{
					if (it.second->GetType() == TYPE_FOLDER)
					{
						que_com.push_back(it.second);
					}
				}
				folder->Remove(file_name);
			}
		}
	}
	else
	{
		Component *father_node = node->GetFaterNode();
		father_node->Remove(node->GetName());
	}
}

CommandDel::~CommandDel()
{
}