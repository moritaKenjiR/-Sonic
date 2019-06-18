#pragma once
#include <memory>
class SceneMng;
class Input;

///ｱﾌﾟﾘｹｰｼｮﾝ全体を制御する
///ｼﾝｸﾞﾙﾄﾝｸﾗｽ
class Application
{
public:
	~Application();
	static Application& Instance()
	{
		static Application Instance;
		return Instance;
	}

	//ｱﾌﾟﾘｹｰｼｮﾝ初期化関数
	bool Initialize(void);

	void InitializeInput();

	//ｱﾌﾟﾘｹｰｼｮﾝを実行する(ｹﾞｰﾑﾙｰﾌﾟ)
	void Run(void);

	//終了処理
	void Terminate(void);
private:
	//生成、コピー、代入禁止
	Application();
	Application(const Application&);
	void operator=(const Application&);

	std::unique_ptr<SceneMng> _sceneMng;
	std::unique_ptr<Input> _input;
};

