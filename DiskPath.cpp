#include "DiskPath.h"

DiskPath::DiskPath()
{
}

//设置当前路径列表的根节点
void DiskPath::SetListHead(Component* component, const string& component_name)
{
	path_list_.clear();
	path_list_.push_front(make_pair(component_name, component));
}

//获取根节点
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

//获取当前路径,字符串型
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

//获取当前路径，列表型
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

//判断路径是否重合
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

//清空列表
void DiskPath::ClearDiskPath()
{
	path_list_.clear();
}

//更新当前路径
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

//判断最终节点是否为链接类型，并记录链接节点
Component* DiskPath::ContainNodeIsSym(list<string>& input_path)
{
	string node_name = input_path.back();
	input_path.pop_back();
	Component* father_node = ContainNode(input_path);
	Component* node = father_node->GetNodeByName(node_name);
	return node;
}

//判断路径是否正确,返回对应组件
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
		if (cur_folder->GetType() == TYPE_FOLDER)//对应文件夹
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
					//链接文件类型
					SymbolLink* link_node = static_cast<SymbolLink *>(cur_folder);
					list<string> link_path = link_node->GetListLinkpath();
					Component* match_link_node = ContainNode(link_path);
					if (match_link_node == nullptr)
					{
						cout << "链接文件被删除" << endl;
						continue;;
					}
					cur_folder = match_link_node;
					continue;
				}
			}
		}
		else //文件类型
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

//通配符路径匹配
Component* DiskPath::ContainWildPath(list<string> &input_path, list<Component *> &component_list , int &flag)
{
	string str = input_path.back();
	if (StringDeal::IsHaveWildCard(str))
	{
		flag = 1;
		//含通配符字符串
		input_path.pop_back();
		Component* match_node = ContainNode(input_path);
		if (match_node == nullptr)
		{
			cout << "找不到路径" << endl;
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
			cout << "通配符匹配不成功" << endl;
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