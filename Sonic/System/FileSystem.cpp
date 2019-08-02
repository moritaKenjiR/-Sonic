#include "FileSystem.h"
#include <windows.h>
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

std::string GetFolderPath(const std::string & path)
{
	auto actsep1 = path.find_last_of('/');
	actsep1 = actsep1 == std::string::npos ? 0 : actsep1;
	auto actsep2 = path.find_last_of('\\');
	actsep2 = actsep2 == std::string::npos ? 0 : actsep2;
	auto separator = max(actsep1, actsep2);
	return path.substr(0, separator+1);
}
