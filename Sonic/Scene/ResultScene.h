#pragma once
#include "BaseScene.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene(SceneMng& mng);
	~ResultScene();
	void Update( Input& input)override final;
	void Draw()override final;
};

