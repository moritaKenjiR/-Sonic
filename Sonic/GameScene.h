#pragma once
#include "BaseScene.h"
class GameScene :
	public BaseScene
{
public:
	~GameScene();
	void Update(const Input& input);
	void Draw()override;
};

