#pragma once

class Data {
public:
	//このﾃﾞｰﾀが使用可能かどうかを返す
	virtual bool IsAvaillable() = 0;
	virtual ~Data() {};
};

class Loader
{
public:
	Loader();
	virtual ~Loader();

	//ﾛｰﾄﾞ
	//@param path ﾌｧｲﾙのﾊﾟｽ
	//@param data ﾃﾞｰﾀｵﾌﾞｼﾞｪｸﾄへの参照
	virtual bool Load(const char* path, Data& data) = 0;

	//ﾃﾞｰﾀのｱﾝﾛｰﾄﾞ
	//@attention これで指定されたﾊﾟｽに対応するﾃﾞｰﾀは
	//ﾒﾓﾘ上から消えるので再度使用する際はｽﾄﾚｰｼﾞｱｸｾｽが発生します。
	virtual void Unload(const char* path) = 0;
};

