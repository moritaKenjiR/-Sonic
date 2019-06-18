#pragma once
#include "BaseScene.h"
class ResultScene :
	public BaseScene
{
public:
	~ResultScene();
	void Update(const Input& input);
	void Draw()override;
};

