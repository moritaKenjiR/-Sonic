#include "Playing3DScene.h"
#include <DxLib.h>
#include "../Input/Input.h"
#include "ResultScene.h"

Playing3DScene::Playing3DScene(SceneMng& mng):BaseScene(mng)
{
	_modelH = MV1LoadModel("model/sonic.pmx");
	MV1SetPosition(_modelH, VGet(0, 0, 0));
	SetCameraNearFar(1.0f, 100.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 15, -30), VGet(0, 1, 0));
	SetupCamera_Perspective(45 * DX_PI_F / 180.0f);
	_attachH = MV1AttachAnim(_modelH, 0);
}


Playing3DScene::~Playing3DScene()
{
}

void Playing3DScene::Update(const Input & input)
{
	auto pos = MV1GetPosition(_modelH);
	auto rot = MV1GetRotationXYZ(_modelH);

	auto totalTime = MV1GetAttachAnimTotalTime(_modelH, _attachH);
	MV1SetAttachAnimTime(_modelH, _attachH, totalTime);
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
		pos.x -= 0.5f;
	}
	if (input.Ispressed(0, "right"))
	{
		pos.x += 0.5f;
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
		rot.y += 0.1f;
	}
	MV1SetRotationXYZ(_modelH, rot);
	MV1SetPosition(_modelH, pos);
	if (input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<ResultScene>(_mng));
	}
}

void Playing3DScene::Draw()
{
	MV1DrawModel(_modelH);
	DrawString(100, 100, "Playing3DScene", 0xffffff);
}
