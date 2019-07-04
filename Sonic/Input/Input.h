#pragma once
#include <memory>
#include <map>
#include <unordered_map>

struct  PeripheralInfo {
	PeripheralInfo() {};
	PeripheralInfo(int perin, int cd) :periNo(perin), code(cd) {};
	int periNo;		// 周辺機器番号
	int code;		//周辺機器の生ｺｰﾄﾞ
	struct HashFunc 
	{
		size_t operator()(const PeripheralInfo& p)const
		{
			return p.periNo | (p.code << 4);
		}
	};
};

bool operator<(const PeripheralInfo & lval, const  PeripheralInfo & rval);
bool operator==(const PeripheralInfo & lval, const  PeripheralInfo & rval);
bool operator!=(const PeripheralInfo & lval, const  PeripheralInfo & rval);

class Input
{
public:
	Input();
	~Input();

	//接続されたﾊﾟｯﾄﾞ数を返す
	int GetConnectedPadCount(void)const;

	//ﾌﾟﾚｲﾔｰ数の設定
	void SetPlayerCount(int plcount);

	//ｺﾏﾝﾄﾞの設定
	//@param plNo ﾌﾟﾚｲﾔｰ番号
	//@param cmd ｺﾏﾝﾄﾞ名
	//@param periNo 周辺機器番号
	//@param code 入力ｺｰﾄﾞ
	void AddCommand(int plNo, std::string cmd, int periNo, int code);

	//情報更新
	//@remarks 毎ﾌﾚｰﾑ呼び出し
	void Update(void);
	
	//押されているかの確認
	bool Ispressed(int plNo, std::string cmd)const;

	//押されたかの確認
	bool IsTriggered(int plNo, std::string cmd)const;

	bool IsReleasd(int plNo, std::string cmd)const;

private:
	char _keystate[256];				//現在のキーボード状況
	std::vector<int> _padstate;	//現在のﾊﾟｯﾄﾞ状況
	

	std::vector<std::multimap<std::string, PeripheralInfo>> _inputTable;//ﾌﾟﾚｲﾔｰ番号と入力対応ﾃｰﾌﾞﾙのｾｯﾄ
	std::unordered_map < PeripheralInfo, std::pair<int, std::string>,PeripheralInfo::HashFunc> _inputMap;//入力情報と利用情報のｾｯﾄ 
	std::vector<std::unordered_map<std::string, bool>> _currentState; //ﾎﾞﾀﾝが押下情報のﾘｽﾄ
	std::vector<std::unordered_map<std::string, bool>> _lastState; //直前のﾎﾞﾀﾝ押下情報のﾘｽﾄ
};

