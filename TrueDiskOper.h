#pragma warning(disable:4244)
#include <windows.h>
#include <io.h>
#include <fstream>
#include "FileDisk.h"
#include "File.h"


//真实磁盘的操作
class TrueDiskOper
{
public:
	TrueDiskOper();
	virtual ~TrueDiskOper();

public:
	static bool IsTrueDiskPath(string &path);//判断是否为真实磁盘路径，是并去除@字符
	static vector<unsigned char> ReadFileFromTrueDisk(string &path);//从真实磁盘中读取文件数据
	static bool GetFilsName(const string &true_path, vector<string> &files_name);//获取目录下所有文件名
	static bool IsFileOrFolder(const string &true_path, string &file_name);//判断为文件或文件夹，true为文件，false为文件夹

public:
	static void WriteDataToTrueDisk(const string &path, Component *component);//写虚拟磁盘数据到真实磁盘
	static void WriteInt(const string &path, int size);//写整型变量
	static void Writestring(const string &path, string &str);//写字符串变量
	static Component* ReadDataFromTrueDisk(ifstream &load_file);//从真实磁盘中读磁盘文件
	static int ReadInt(ifstream &load_file);//读整型变量
	static string Readstring(ifstream &load_file);//读字符串变量
};


