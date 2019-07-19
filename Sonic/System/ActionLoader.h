#pragma once
#include <map>
#include <vector>
#include <string>
#include "System/Loader.h"
class ActionLoader :
	public Loader
{
public:
	ActionLoader();
	~ActionLoader();

	bool Load(const char* path, Data& data)override;
	void Unload(const char* path)override;

	using Bytes_t = std::vector<unsigned char>;
private:
	using Table_t = std::map<std::string, Bytes_t>;

	Table_t _table;
};

class ActionData : public Data
{
	friend ActionLoader;
public:
	ActionLoader::Bytes_t* GetRawData();
private:
	ActionLoader::Bytes_t* _data;
};

