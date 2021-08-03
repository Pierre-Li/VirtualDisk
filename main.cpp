#include "VirtualDisk.h"

int main()
{
	VirtualDisk *Disk = VirtualDisk::Instance();
	Disk->GetCmdStr();
	return 0;
}