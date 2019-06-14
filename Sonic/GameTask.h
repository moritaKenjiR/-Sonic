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
	//�����A�R�s�[�A����֎~
	GameTask();
	GameTask(const GameTask&);
	void operator= (const GameTask&);


};

