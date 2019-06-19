#pragma once
#include "BaseScene.h"
class PauseScene :
	public BaseScene
{
public:
	PauseScene(SceneMng& mng);
	~PauseScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

