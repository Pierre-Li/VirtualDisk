#include "Factory.h"


Factory::Factory()
{
}

BaseCommand* Factory::CreateCommand(const string& command_name)
{
	if (command_name == "dir")
	{
		return new CommandDir();
	} 
	else if (command_name == "md")
	{
		return new CommandMd();
	} 
	else if (command_name == "rd")
	{
		return new CommandRd;
	}
	else if (command_name == "cd")
	{
		return new CommandCd;
	}
	else if(command_name == "del")
	{
		return new CommandDel;
	}
	else if(command_name == "copy")
	{
		return new CommandCopy;
	}
	else if(command_name == "ren")
	{
		return new CommandRen;
	}
	else if (command_name == "move")
	{
		return new CommandMove;
	}
	else if (command_name == "mklink")
	{
		return new CommandMklink;
	}
	else if (command_name == "save")
	{
		return new CommandSave;
	}
	else if (command_name == "load")
	{
		return new CommandLoad;
	}
	else if (command_name == "cls")
	{
		return new CommandCls;
	}
	cout <<"ÃüÁî¸ñÊ½´íÎó" <<endl;
	return nullptr;
}

Factory::~Factory()
{
}