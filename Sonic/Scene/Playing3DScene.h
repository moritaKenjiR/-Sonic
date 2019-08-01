#pragma once
#include "BaseScene.h"
class Playing3DScene :
	public BaseScene
{
public:
	Playing3DScene(SceneMng& mng);
	~Playing3DScene();

	void Update(const Input& input)override final;
	void Draw()override final;
private:
	int _modelH;
	int _attachH;
	int _animTime;
};

