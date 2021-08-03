#include "FileDisk.h"

FileDisk::FileDisk()
{
	root = new Folder(nullptr, "C:", TYPE_FOLDER);
}

Component* FileDisk::GetRootNode()
{
	return root;
}

void FileDisk::FormatDisk()
{
	if (root != nullptr)
	{
		delete root;
	}
	root = new Folder(nullptr, "C:", TYPE_FOLDER);
}

void FileDisk::SetRootNode(Component* component_root)
{
	root = component_root;
}

FileDisk::~FileDisk()
{
	delete root;
}