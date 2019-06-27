#pragma once
#include "BaseScene.h"
class PauseScene :
	public BaseScene
{
public:
	PauseScene(SceneMng& mng);
	~PauseScene();
	void Update( Input& input)override final;
	void Draw()override final;
};

