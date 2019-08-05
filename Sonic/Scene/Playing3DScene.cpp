#include "Playing3DScene.h"
#include <DxLib.h>
#include "../Input/Input.h"
#include "ResultScene.h"
#include "../Application.h"



struct Camera3D
{
	VECTOR eye;
	VECTOR target;
	VECTOR viewray;
};

Playing3DScene::Playing3DScene(SceneMng& mng):BaseScene(mng)
{


	_camera = std::make_shared<Camera3D>();
	_camera->eye = VGet(0, 15, -100);
	_camera->target = VGet(0, 25, 0);
	_camera->viewray = VSub(_camera->target, _camera->eye);
	_modelH = MV1LoadModel("model/TdaŽ®‰‰¹ƒ~ƒNV4X.pmx");
	MV1SetPosition(_modelH, VGet(0, 25, 0));
	SetCameraNearFar(1.0f, 100.0f);
	SetCameraPositionAndTarget_UpVecY(_camera->eye, _camera->target);
	SetupCamera_Perspective(60 * DX_PI_F / 180.0f);
	_attachH = MV1AttachAnim(_modelH, 1);
	_animTime = 0;
	_radian = 0.0f;

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
}


Playing3DScene::~Playing3DScene()
{
}

void Playing3DScene::Update(const Input & input)
{
	auto sp_pos = (VGet(0, 0, 0));
	auto U = VGet(0, 1, 0);
	auto pos = MV1GetPosition(_modelH);
	auto rot = MV1GetRotationXYZ(_modelH);
	auto N = VNorm(VSub(pos, sp_pos));

	auto totalTime = MV1GetAttachAnimTotalTime(_modelH, _attachH);
	_animTime += 0.5f;
	if (_animTime >= totalTime) _animTime = 0;
	MV1SetAttachAnimTime(_modelH, _attachH, _animTime);
	auto cross = VCross(U, _camera->viewray);
	VNorm(cross);
	auto v = VCross(cross, U);
	VNorm(v);
	MV1SetRotationZYAxis(_modelH, VScale(v, -1), U, 0.0f);

	if (input.Ispressed(0, "up"))
	{
		pos.z += 1.0f;
		_camera->eye.z += 1.0f;
	}
	if (input.Ispressed(0, "down"))
	{
		pos.z -= 1.0f;
		_camera->eye.z -= 1.0f;
		
	}
	if (input.Ispressed(0, "left"))
	{
		pos.x -= 1.0f;
		_radian -= 0.01f;
	//	_camera->viewray.x -= 2.0f;
		_camera->eye.x -= 1.0f;
		
	}
	if (input.Ispressed(0, "right"))
	{
		_radian += 0.01f;
		pos.x += 1.0f;

		//_camera->viewray.x += 0.5f;
		_camera->eye.x += 1.0f;
		
		
	}
	if (input.Ispressed(0, "forward"))
	{
		_camera->viewray.x += 0.5;
		_camera->viewray.z += 0.5;
	}
	if (input.Ispressed(0, "back"))
	{
		_camera->viewray.x -= 0.5;
		_camera->viewray.z -= 0.5;
	}
	if (input.Ispressed(0, "rotate"))
	{
		//rot.y += 0.1f;
		_radian += 0.05f;
	}
	//auto mat = MGetRotY(_radian);
	//VTransformSR(_camera->viewray, mat);
	_camera->target = VGet(pos.x, pos.y, pos.z);
	SetCameraPositionAndTarget_UpVecY(_camera->eye, _camera->target);
	MV1SetRotationXYZ(_modelH, rot);
	MV1SetPosition(_modelH, pos);
	

	if (input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<ResultScene>(_mng));
	}
}

void Playing3DScene::Draw()
{
	//SetCameraPositionAndTarget_UpVecY(VAdd(_camera->eye,_camera->viewray),_camera->target);
	//DrawCube();
	DrawSphere3D(VGet(0, 0, 0), 32, 32, 0x88ffaa, 0xffffff, true);
	MV1DrawModel(_modelH);
	DrawString(100, 100, "Playing3DScene", 0xffffff);
}

void Playing3DScene::DrawCube()
{
	constexpr float tile_size = 25.0f;
	auto lefttop = VGet(-tile_size / 2, 0, -tile_size / 2);
	auto rightbottom = VGet(tile_size / 2, -1, tile_size / 2);
	int a = 0;
	auto wsize = Application::Instance().GetConfig().GetScreenSize();
	for (int j = -4; j < 5; ++j) {
		for (int i = -4; i < 5; ++i) {
			auto vtop = lefttop;
			auto vbottom = rightbottom;
			vtop.x += i * tile_size;
			vtop.z += j * tile_size;
			vbottom.x += i * tile_size;
			vbottom.z += j * tile_size;
			a = (abs(j) + abs(i)) * 32;
			auto col = GetColor((255 - a), 128 + a, 255);
			DxLib::DrawCube3D(vbottom, vtop, col, 0xffffff, true);
		}
	}
}
