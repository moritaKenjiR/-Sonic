#pragma once
#include "BaseScene.h"
class SceneMng;

class TitleScene :
	public BaseScene
{
public:
	TitleScene(SceneMng& mng);
	~TitleScene();
	void Update(const Input& input);
	void Draw()override;
};

