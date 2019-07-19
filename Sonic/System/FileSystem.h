#pragma once
#include <memory>
#include <map>
class Loader;
class Data;

class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	bool Load(const char* path, Data& data);
private:
	std::unique_ptr<Loader> _imageLoader;
	std::unique_ptr<Loader> _actionLoader;
	std::unique_ptr<Loader> _levelLoader;
	std::map<std::string, std::shared_ptr<Loader>> _loaders;
};

