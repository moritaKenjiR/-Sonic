#include "FileSystem.h"
#include "ImageLoader.h"
#include "ActionLoader.h"
#include "Loader.h"

std::string GetExtension(const char* path)
{
	std::string str = path;
	auto idx = str.rfind('.')+1;
	return str.substr(idx, str.length() - idx);
}

FileSystem::FileSystem()
{
	auto imgLoader = std::make_shared<ImageLoader>();
	auto actLoader = std::make_shared<ActionLoader>();

	_loaders["bmp"] = _loaders["jpg"] = _loaders["png"] = imgLoader;
	_loaders["act"] = actLoader;
}


FileSystem::~FileSystem()
{
}

bool FileSystem::Load(const char * path, Data & data)
{
	auto ext = GetExtension(path);
	return _loaders[ext]->Load(path,data);
}
