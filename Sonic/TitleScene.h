#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	~TitleScene();
	void Update(const Input& input);
	void Draw()override;
};

