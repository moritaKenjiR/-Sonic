#pragma once
#include "BaseScene.h"
class PauseScene :
	public BaseScene
{
public:
	~PauseScene();
	void Update(const Input& input)override;
	void Draw()override;
};

