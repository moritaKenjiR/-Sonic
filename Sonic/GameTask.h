#pragma once
#include <memory>
class SceneMng;
class Input;

class GameTask
{
public:
	~GameTask();
	static GameTask& GetInstance() {
		static GameTask Instance;
		return Instance;
	}

	void Init(void);
	void Run(void);
private:
	//生成、コピー、代入禁止
	GameTask();
	GameTask(const GameTask&);
	void operator= (const GameTask&);


};

