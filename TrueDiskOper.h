#pragma warning(disable:4244)
#include <windows.h>
#include <io.h>
#include <fstream>
#include "FileDisk.h"
#include "File.h"


//��ʵ���̵Ĳ���
class TrueDiskOper
{
public:
	TrueDiskOper();
	virtual ~TrueDiskOper();

public:
	static bool IsTrueDiskPath(string &path);//�ж��Ƿ�Ϊ��ʵ����·�����ǲ�ȥ��@�ַ�
	static vector<unsigned char> ReadFileFromTrueDisk(string &path);//����ʵ�����ж�ȡ�ļ�����
	static bool GetFilsName(const string &true_path, vector<string> &files_name);//��ȡĿ¼�������ļ���
	static bool IsFileOrFolder(const string &true_path, string &file_name);//�ж�Ϊ�ļ����ļ��У�trueΪ�ļ���falseΪ�ļ���

public:
	static void WriteDataToTrueDisk(const string &path, Component *component);//д����������ݵ���ʵ����
	static void WriteInt(const string &path, int size);//д���ͱ���
	static void Writestring(const string &path, string &str);//д�ַ�������
	static Component* ReadDataFromTrueDisk(ifstream &load_file);//����ʵ�����ж������ļ�
	static int ReadInt(ifstream &load_file);//�����ͱ���
	static string Readstring(ifstream &load_file);//���ַ�������
};


