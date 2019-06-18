#pragma once
#include "BaseScene.h"
class GameScene :
	public BaseScene
{
public:
	GameScene(SceneMng& mng);
	~GameScene();
	void Update(const Input& input);
	void Draw()override;
};

