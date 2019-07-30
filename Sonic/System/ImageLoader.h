#pragma once
#include <map>
#include "Loader.h"

class ImageLoader :
	public Loader
{
public:
	ImageLoader();
	~ImageLoader();

	bool Load(const char* path, Data& data)override;
	void Unload(const char* path)override;
private:
	using HandleTable_t = std::map<std::string, int>;
	HandleTable_t _table;
};

class ImageData : public Data{
	friend ImageLoader;
public:
	int GetHandle()const;
	bool IsAvaillable();
private:
	int _handle;
};

