#include "TrueDiskOper.h"

TrueDiskOper::TrueDiskOper()
{
}

//是否为真实路径
bool TrueDiskOper::IsTrueDiskPath(string & is_path)
{
	if (is_path.size() != 0 && is_path[0] == '@')
	{
		is_path.erase(is_path.begin());
		return true;
	}
	return false;
}

//读真实文件
vector<unsigned char> TrueDiskOper::ReadFileFromTrueDisk(string & true_path)
{
	vector<unsigned char> file_data;
	ifstream read_file(true_path, ios::binary);
	read_file.seekg(0, ios::end);
	file_data.resize(read_file.tellg());
	read_file.seekg(0);
	read_file.read(reinterpret_cast<char*>(file_data.data()), file_data.size());
	read_file.close();
	return file_data;
}

//判断真实路径为文件还是目录
bool TrueDiskOper::IsFileOrFolder(const string& true_path, string &file_name)
{
	list<string> file_path;
	string str;
	for (unsigned int i = 0; i < true_path.size(); i++)
	{
		if (i == true_path.size() || true_path[i] == '\\')
		{
			file_path.push_back(str);
			str = "";
			continue;
		}
		str += true_path[i];
	}
	file_path.push_back(str);
	for (auto it : file_path.back())
	{
		if (it == '.' && file_path.back() != "." && file_path.back() != "..")
		{
			file_name = file_path.back();
			return true;
		}
	}
	return false;
}

//获取真实路径目录下所有文件名
bool TrueDiskOper::GetFilsName(const string& true_path, vector<string>& files_name)
{
	vector<string> vect;
	struct _finddata_t file;
	long lf;
	string src = true_path + "\\*.*";
	lf = _findfirst(src.c_str(), &file);
	if (lf == -1)
	{
		return false;
	}
	else
	{
		while (_findnext(lf, &file) == 0)
		{
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
				continue;
			vect.push_back(file.name);
		}
	}
	for (auto it : vect)
	{
		if (it.find('.') != string::npos)
		{
			files_name.push_back(it);
		}
	}
	_findclose(lf);
	return true;
}

//文件存储结构体
struct temporary
{
	int _type;
	string _name;
	string _time;
	int _size;
	string _conent;
	string _linkpath;
};

//写整型
void TrueDiskOper::WriteInt(const string& path, int num)
{
	ofstream save_file(path.c_str(), ios::binary | ios::app);
	save_file.write((char*)&num, sizeof(num));
	save_file.close();
}

//写字符串
void TrueDiskOper::Writestring(const string& path, string& str)
{
	ofstream save_file(path.c_str(), ios::binary | ios::app);
	const char *p = str.c_str();
	int len = str.size();
	WriteInt(path, len);
	save_file.write((char *)p, len);
	save_file.close();
}

//写数据
void TrueDiskOper::WriteDataToTrueDisk(const string& path, Component* component)
{
	temporary tem;
	tem._type = component->GetType();
	string _name = component->GetName();
	tem._name = _name;
	string _time = component->GetTime();
	tem._time = _time;
	WriteInt(path, tem._type);
	Writestring(path, tem._name);
	Writestring(path, tem._time);
	if (component->GetType() == TYPE_FOLDER)
	{
		Folder* folder = static_cast<Folder *>(component);
		tem._size = folder->cmap_.size();
		WriteInt(path, tem._size);
	}
	else if (component->GetType() == TYPE_FILE)
	{
		int num;
		vector<unsigned char> vect;
		File* _file = static_cast<File *>(component);
		vect = _file->GetContent(num);
		string str = "";
		for (auto it : vect)
		{
			str += it;
		}
		tem._conent = str;
		Writestring(path, tem._conent);
	}
	else if (component->GetType() == TYPE_LINK_FILE || component->GetType() == TYPE_LINK_FOLDER)
	{
		SymbolLink* _symb = static_cast<SymbolLink *>(component);
		tem._linkpath = _symb->GetLink();
		Writestring(path, tem._linkpath);
	}
}

//读整型
int TrueDiskOper::ReadInt(ifstream &load_file)
{
	int _size;
	load_file.read((char*)&_size, sizeof(_size));
	return _size;
}

//读字符串型
string TrueDiskOper::Readstring(ifstream &load_file)
{
	int len, i = 0;
	len = ReadInt(load_file);
	string str;
	char tem;
	for (i; i < len; i++)
	{
		load_file.read((char*)&tem, sizeof(tem));
		str += tem;
	}
	return str;
}

Component* TrueDiskOper::ReadDataFromTrueDisk(ifstream& load_file)
{
	temporary tem1;
	tem1._type = ReadInt(load_file);
	tem1._name = Readstring(load_file);
	tem1._time = Readstring(load_file);
	string name_str = tem1._name;
	string the_time = tem1._time;
	if (tem1._type == TYPE_FOLDER) //读文件夹添加_cmap.size
	{
		tem1._size = ReadInt(load_file);
		int node_size = tem1._size;
		Folder* folder = new Folder(nullptr, name_str, tem1._type);
		folder->SetTime(the_time);
		folder->SetSize(node_size);
		return folder;
	}
	else if (tem1._type == TYPE_FILE) //读文件添加_conent
	{
		vector<unsigned char> vect;
		tem1._conent = Readstring(load_file);
		vect.assign(tem1._conent.begin(), tem1._conent.end());
		File* _file = new File(nullptr, name_str, tem1._type);
		_file->SetTime(the_time);
		_file->WriteContent(vect, vect.capacity());
		return _file;
	}
	else if (tem1._type == TYPE_LINK_FILE || tem1._type == TYPE_LINK_FOLDER) //读mklink添加_linkpath
	{
		string _link;
		tem1._linkpath = Readstring(load_file);
		_link = tem1._linkpath;
		SymbolLink* symlink = new SymbolLink(nullptr, name_str, tem1._type);
		symlink->SetTime(the_time);
		symlink->SetLink(_link);
		return symlink;
	}
	return nullptr;
}

TrueDiskOper::~TrueDiskOper()
{
}