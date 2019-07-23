#pragma once
#include <map>
#include <vector>
#include <string>
#include "Loader.h"
#include "../Game/Player.h"
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
	static void Read(void* dst, size_t& bytenum, int& cursor, ActionData& act);
	//@param actdata ｱｸｼｮﾝﾃﾞｰﾀ[in]
	//@param actset ｱｸｼｮﾝｾｯﾄ[out]
	//@param imgPath そのｱｸｼｮﾝに必要な画像ﾌｧｲﾙのﾊﾟｽ[out]
	static void BuildActionSet(const ActionData& actdata, ActionSet& actset, std::string& imgPath);
private:
	ActionLoader::Bytes_t* _data;
};


