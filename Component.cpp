#include "Component.h"

Component::Component(Component* father_node, const string &name, int type)
{
	father_node_ = father_node;
	name_ = name;
	time_ = NowTime::Instance()->GetNowTime();
	size_ = 0;
	type_ = type;
}

int Component::GetType() const
{
	return type_;
}

int Component::GetSize() const
{
	return size_;
}

const string& Component::GetName() const
{
	return name_;
}

const string& Component::GetTime() const
{
	return time_;
}

Component* Component::GetFaterNode() const
{
	return father_node_;
}

string Component::GetTypeName()const
{
	if (type_ == TYPE_FOLDER)
	{
		return "<DIR>";
	}
	else if (type_ == TYPE_FILE)
	{
		return "";
	}
	else if (type_ == TYPE_LINK_FILE)
	{
		return "SYMLINK";
	}
	else if (type_ == TYPE_LINK_FOLDER)
	{
		return "SYMLINKF";
	}
	else
	{
		return "ERR";
	}
}

void Component::SetSize(int new_size)
{
	size_ = new_size;
}

void Component::SetName(string &new_name)
{
	name_ = new_name;
}

void Component::SetTime(string & new_time)
{
	time_ = new_time;
}

void Component::SetFatherNode(Component * _com)
{

	father_node_ = _com;
}

void Component::Display()
{
	if (type_ == TYPE_FILE)
	{
		cout << time_ << "   " << right << setw(14) << StringDeal::IntToString(size_) << " " << GetName() << endl;

	}
	else
		cout << time_ << "   " << left << setw(15) << GetTypeName() << GetName() << endl;
}

void Component::Add(const string &_name, int _type)
{
	return;
}

void Component::Remove(const string & _name)
{
	return;
}

Component* Component::GetNodeByName(const string & _name)
{
	return GetNodeByName(_name);
}

Component::~Component()
{

}