#include "ActionLoader.h"



ActionLoader::ActionLoader()
{
}


ActionLoader::~ActionLoader()
{
}

bool ActionLoader::Load(const char * path, Data & data)
{
	ActionData& action = dynamic_cast<ActionData&>(data);
	auto it = _table.find(path);
	if (it == _table.end())
	{
		auto size = FileRead_size(path);
		if (size == -1)
		{
			return false;
		}
		_table[path].resize(size);
		auto h = FileRead_open(path);
		FileRead_read(_table[path],size,path)

	}
	else
	{
		action._data = &_table[path];
		return true;
	}
}
