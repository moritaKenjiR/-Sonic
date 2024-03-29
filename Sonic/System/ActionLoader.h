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
private:
	ActionLoader::Bytes_t* _data;
public:
	ActionLoader::Bytes_t* GetRawData();
	static void Read(void* dst, size_t bytenum, size_t& cursor, ActionData& act);
	bool IsAvaillable();
	//@param actdata ｱｸｼｮﾝﾃﾞｰﾀ[in]
	//@param actset ｱｸｼｮﾝｾｯﾄ[out]
	//@param imgPath そのｱｸｼｮﾝに必要な画像ﾌｧｲﾙのﾊﾟｽ[out]
	static void BuildActionSet(const ActionData& actdata, ActionSet_t& actset, std::string& imgPath);

};


