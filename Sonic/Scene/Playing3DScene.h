#pragma once
#include "BaseScene.h"
class Camera3D;

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
	float _animTime;
	float _radian;
	std::shared_ptr<Camera3D> _camera;
};

