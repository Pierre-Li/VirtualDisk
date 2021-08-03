#include "Folder.h"


Folder::Folder(Component* _father_node, const string &_name, int _type) :Component(_father_node, _name, _type)
{
}

void Folder::Add(const string &component_name, int component_type)
{
	Component* tem_component;
	if (component_type == TYPE_FOLDER)//添加文件夹类型
	{
		Folder *new_folder = new Folder(this, component_name, component_type);
		tem_component = new_folder;
	}
	else if (component_type == TYPE_FILE)//添加文件类型
	{
		File* new_file = new File(this, component_name, component_type);
		tem_component = new_file;
	}
	else if (component_type == TYPE_LINK_FILE || TYPE_LINK_FOLDER)//添加符号链接
	{
		SymbolLink* new_symlink = new SymbolLink(static_cast<Component*>(this), component_name, component_type);
		tem_component = new_symlink;
	}
	cmap_.insert(pair<string, Component*>(component_name, tem_component));
}

void Folder::DisplayAll()
{
	int folder_num = 0;
	int file_num = 0;
	int all_size = 0;
	map<string, Component*>::iterator iter = cmap_.begin();
	while (iter != cmap_.end())
	{
		if (iter->second->GetType() == TYPE_FOLDER)
		{
			folder_num += 1;
			iter->second->Display();
		}
		else if (iter->second->GetType() == TYPE_FILE)
		{
			file_num += 1;
			iter->second->Display();
			all_size += iter->second->GetSize();
		}
		else if (iter->second->GetType() == TYPE_LINK_FILE || iter->second->GetType() == TYPE_LINK_FOLDER)
		{
			SymbolLink *sym = static_cast<SymbolLink *>(iter->second);
			sym->Display();
		}
		iter++;
	}
	cout << "         " << file_num << "个文件" << "  " << StringDeal::IntToString(all_size) << "字节" << endl;
	cout << "         " << folder_num << "个目录" << endl;
}

void Folder::DisplayFolder()
{
	int folder_num = 0;
	int file_num = 0;
	int all_size = 0;
	map<string, Component*>::iterator iter1 = cmap_.begin();;
	while (iter1 != cmap_.end())
	{
		if (iter1->second->GetType() == TYPE_FOLDER || iter1->second->GetType() == TYPE_LINK_FOLDER)
		{
			folder_num++;
			iter1->second->Display();
		}
		else if (iter1->second->GetType() == TYPE_FILE || iter1->second->GetType() == TYPE_LINK_FILE)
		{
			file_num += 1;
			all_size += iter1->second->GetSize();
		}
		iter1++;
	}
	cout << "         " << file_num << "个文件" << "  " << StringDeal::IntToString(all_size) << "字节" << endl;
	cout << "         " << folder_num << "个目录" << endl;
}

void Folder::DisplayFile()
{
	int folder_num = 0;
	int file_num = 0;
	int all_size = 0;
	map<string, Component*>::iterator iter1;
	iter1 = cmap_.begin();
	while (iter1 != cmap_.end())
	{
		if (iter1->second->GetType() == TYPE_FOLDER || iter1->second->GetType() == TYPE_LINK_FOLDER)
		{
			RecurTraversel(iter1->second, all_size);
		}
		if (iter1->second->GetType() == TYPE_FILE || iter1->second->GetType() == TYPE_LINK_FILE)
		{
			all_size += iter1->second->GetSize();
			iter1->second->Display();
		}
		iter1++;
	}
	cout << "         " << file_num << "个文件" << "  " << StringDeal::IntToString(all_size) << "字节" << endl;
	cout << "         " << folder_num << "个目录" << endl;
}

void Folder::RecurTraversel(Component* component, int &all_size)
{
	Folder * folder = static_cast<Folder*>(component);
	if (folder->cmap_.size() == 0)
	{
		return;
	}
	for (auto it : folder->cmap_)
	{
		if (it.second->GetType() == TYPE_FOLDER && it.second->GetName() != "." &&  it.second->GetName() != "..")
		{
			RecurTraversel(static_cast<Folder*>(it.second), all_size);
		}
		else
		{
			all_size += it.second->GetSize();
			it.second->Display();
		}
	}
}

void Folder::Remove(const string& node_name)
{
	auto it = cmap_.find(node_name);
	if (it == cmap_.end())
	{
		return;
	}
	Component *com_name = it->second;
	cmap_.erase(node_name);
	delete com_name;
}

void Folder::RecurRemove(Component* folder_node_name, const string& node_name)
{
	Folder * folder = static_cast<Folder*>(folder_node_name);
	for (auto it : folder->cmap_)
	{
		if (it.second->GetType() == TYPE_FOLDER && it.second->GetName() != "." &&  it.second->GetName() != "..")
		{
			RecurRemove(static_cast<Folder*>(it.second), node_name);
		}
		else if (it.second->GetType() == TYPE_FILE && it.second->GetName() == node_name)
		{
			folder->Remove(node_name);
		}
	}
}

Component* Folder::GetNodeByName(const string& find_name)
{
	auto f_map = cmap_.find(find_name);
	if (f_map == cmap_.end())
	{
		return nullptr;
	}
	return f_map->second;
}

Folder::~Folder()
{
	for (auto it : cmap_)
	{
		delete it.second;
	}
}