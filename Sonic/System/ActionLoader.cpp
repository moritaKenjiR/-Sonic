#include "ActionLoader.h"
#include <DxLib.h>


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
		FileRead_read(&_table[path], size, h);

	}
	else
	{
		action._data = &_table[path];
		return true;
	}
}

ActionLoader::Bytes_t * ActionData::GetRawData()
{
	return _data;
}

void ActionData::Read(void * dst, size_t & bytenum, int & cursor, ActionData & act)
{
	char* tmpdst = (char*)dst;
	std::copy(act.GetRawData()->begin() + cursor,
		act.GetRawData()->begin() + cursor + bytenum, tmpdst);
	cursor += bytenum;
}

void ActionData::BuildActionSet(const ActionData & actdata, ActionSet_t & actset, std::string & imgPath)
{
}
