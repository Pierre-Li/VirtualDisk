#include "DiskPath.h"

DiskPath::DiskPath()
{
}

//���õ�ǰ·���б�ĸ��ڵ�
void DiskPath::SetListHead(Component* component, const string& component_name)
{
	path_list_.clear();
	path_list_.push_front(make_pair(component_name, component));
}

//��ȡ���ڵ�
Component* DiskPath::GetRootNode()
{
	if (path_list_.size() != 0)
	{
		return path_list_.front().second;
	}
	else
	{
		return nullptr;
	}
}

//��ȡ��ǰ·��,�ַ�����
string DiskPath::GetCurPath()
{
	string cur_path;
	bool flag = true;
	for (auto it:path_list_)
	{
		cur_path += flag ? "" : "\\" ;
		cur_path += it.first;
		flag = false;
	}
	if (path_list_.size() == 1)
		cur_path += "\\";
	return cur_path;
}

//��ȡ��ǰ·�����б���
list<string> DiskPath::GetListCurPath()
{
	list<string> cur_path;
	string tem;
	for (auto it : path_list_)
	{
		tem = it.first;
		transform(tem.begin(), tem.end(), tem.begin(), ::tolower);
		cur_path.push_back(tem);
	}
	return cur_path;
}

//�ж�·���Ƿ��غ�
bool DiskPath::ListContain(Component *node, DiskPath *cur_path)
{
	for (auto it : path_list_)
	{
		if (it.second == node)
		{
			return true;
		}
	}
	return false;
}

//����б�
void DiskPath::ClearDiskPath()
{
	path_list_.clear();
}

//���µ�ǰ·��
void DiskPath::UpdateCurPath(list<string> &input_path)
{
	Component* path_node;
	path_node = GetRootNode();
	path_list_.clear();
	path_list_.push_back(pair<string, Component*>(path_node->GetName(), path_node));
	for (auto it : input_path)
	{
		if (it == "..")
		{
			path_node = path_node->GetFaterNode();
			path_list_.pop_back();
			continue;
		}
		if (it == ".")
		{
			continue;
		}
		if (path_node->GetType() == TYPE_FOLDER)
		{
			Component *node = path_node->GetNodeByName(it);
			path_list_.push_back(pair<string, Component*>(node->GetName(), node));
			path_node = node;
			if (path_node->GetType() == TYPE_LINK_FOLDER)
			{
				SymbolLink *sym_node = static_cast<SymbolLink *>(path_node);
				list<string> list_sym = sym_node->GetListLinkpath();
				Component* com_sym = ContainNode(list_sym);
				path_node = com_sym;
			}
		}
	}
}

//�ж����սڵ��Ƿ�Ϊ�������ͣ�����¼���ӽڵ�
Component* DiskPath::ContainNodeIsSym(list<string>& input_path)
{
	string node_name = input_path.back();
	input_path.pop_back();
	Component* father_node = ContainNode(input_path);
	Component* node = father_node->GetNodeByName(node_name);
	return node;
}

//�ж�·���Ƿ���ȷ,���ض�Ӧ���
Component* DiskPath::ContainNode(list<string>& input_path)
{
	Component* cur_folder;
	bool FLAG = true;
	cur_folder = GetRootNode();
	if (input_path.size() != 0)
	{
		input_path.pop_front();
	}
	for (auto it : input_path)
	{
		if (it == "..")
		{
			if (cur_folder->GetFaterNode() == nullptr)
			{
				return nullptr;
			}
			else
			{
				cur_folder = cur_folder->GetFaterNode();
			}
			continue;
		}
		if (it == ".")
		{
			continue;
		}
		if (cur_folder->GetType() == TYPE_FOLDER)//��Ӧ�ļ���
		{
			Component* match_node = cur_folder->GetNodeByName(it);
			if (match_node == nullptr)
			{
				FLAG = false;
				break;
			}
			else
			{
				cur_folder = match_node;
				if (cur_folder->GetType() == TYPE_LINK_FOLDER || cur_folder->GetType() == TYPE_LINK_FILE)
				{
					//�����ļ�����
					SymbolLink* link_node = static_cast<SymbolLink *>(cur_folder);
					list<string> link_path = link_node->GetListLinkpath();
					Component* match_link_node = ContainNode(link_path);
					if (match_link_node == nullptr)
					{
						cout << "�����ļ���ɾ��" << endl;
						continue;;
					}
					cur_folder = match_link_node;
					continue;
				}
			}
		}
		else //�ļ�����
		{
			FLAG = false;
			break;
		}
	}
	if (FLAG)
	{
		return cur_folder;
	}
	else
	{
		return nullptr;
	}
}

//ͨ���·��ƥ��
Component* DiskPath::ContainWildPath(list<string> &input_path, list<Component *> &component_list , int &flag)
{
	string str = input_path.back();
	if (StringDeal::IsHaveWildCard(str))
	{
		flag = 1;
		//��ͨ����ַ���
		input_path.pop_back();
		Component* match_node = ContainNode(input_path);
		if (match_node == nullptr)
		{
			cout << "�Ҳ���·��" << endl;
			return nullptr;
		}
		Folder* folder = static_cast<Folder *>(match_node);
		for (auto it:folder->cmap_)
		{

			if (StringDeal::MatchsWildCard(it.first, str))
			{
				component_list.push_back(it.second);
			}
		}
		if (component_list.size() == 0)
		{
			cout << "ͨ���ƥ�䲻�ɹ�" << endl;
			return nullptr;
		}
		return match_node;
	}
	else
	{
		return ContainNode(input_path);
		flag = 0;
	}
}

DiskPath::~DiskPath()
{
}