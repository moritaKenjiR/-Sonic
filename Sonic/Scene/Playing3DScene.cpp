#include "Playing3DScene.h"
#include <DxLib.h>
#include "../Input/Input.h"
#include "ResultScene.h"

struct Camera3D
{
	VECTOR eye;
	VECTOR target;
	VECTOR viewray;
};

Playing3DScene::Playing3DScene(SceneMng& mng):BaseScene(mng)
{
	_camera = std::make_shared<Camera3D>();
	_camera->eye = VGet(0, 5, -30);
	_camera->target = VGet(0, 0, 0);
	_camera->viewray = VSub(_camera->target, _camera->eye);
	_modelH = MV1LoadModel("model/Ryza.pmx");
	MV1SetPosition(_modelH, VGet(0, -15, 10));
	SetCameraNearFar(1.0f, 100.0f);
	SetCameraPositionAndTarget_UpVecY(_camera->eye, _camera->target);
	SetupCamera_Perspective(45 * DX_PI_F / 180.0f);
	_attachH = MV1AttachAnim(_modelH, 0);
	_animTime = 0;
	_radian = 0.0f;
}


Playing3DScene::~Playing3DScene()
{
}

void Playing3DScene::Update(const Input & input)
{
	auto pos = MV1GetPosition(_modelH);
	auto rot = MV1GetRotationXYZ(_modelH);

	auto totalTime = MV1GetAttachAnimTotalTime(_modelH, _attachH);
	_animTime += 0.5f;
	if (_animTime >= totalTime) _animTime = 0;
	MV1SetAttachAnimTime(_modelH, _attachH, _animTime);

	if (input.Ispressed(0, "up"))
	{
		pos.y += 0.5f;
	}
	if (input.Ispressed(0, "down"))
	{
		pos.y -= 0.5f;
	}
	if (input.Ispressed(0, "left"))
	{
		//pos.x -= 0.5f;
		_radian -= 0.01f;
		_camera->viewray.x -= 2.0f;
		_camera->eye.x -= 2.0f;
		_camera->target.x -= 2.0f;
	}
	if (input.Ispressed(0, "right"))
	{
		_radian += 0.01f;
		//pos.x += 0.5f;

		_camera->viewray.x += 2.0f;
		_camera->eye.x += 2.0f;
		_camera->target.x += 2.0f;
		
	}
	if (input.Ispressed(0, "forward"))
	{
		pos.z += 0.5f;
	}
	if (input.Ispressed(0, "back"))
	{
		pos.z -= 0.5f;
	}
	if (input.Ispressed(0, "rotate"))
	{
		//rot.y += 0.1f;
		_radian += 0.05f;
	}
	auto mat = MGetRotY(_radian);
	VTransformSR(_camera->viewray, mat);
	MV1SetRotationXYZ(_modelH, rot);
	MV1SetPosition(_modelH, pos);

	if (input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<ResultScene>(_mng));
	}
}

void Playing3DScene::Draw()
{
	SetCameraPositionAndTarget_UpVecY(VAdd(_camera->eye,_camera->viewray),_camera->target);
	MV1DrawModel(_modelH);
	DrawString(100, 100, "Playing3DScene", 0xffffff);
}
