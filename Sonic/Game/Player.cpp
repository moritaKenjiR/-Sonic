#include "Player.h"
#include <DxLib.h>
#include <math.h>
#include <string>
#include "../Input/Input.h"
#include "Camera.h"
#include "../scene/GameScene.h"
#include"../Ground.h"
#include "action.h"
#include "../System/FileSystem.h"
#include "../System/ActionLoader.h"
#include "../System/ImageLoader.h"
#include "../Application.h"

constexpr int default_player_posx = 512;
constexpr int default_player_posy = 500;
constexpr float jump_power = -10.0f;
constexpr float g = 0.3f;

Player::Player(const Camera& cam):Actor(cam,Position2f(default_player_posx,default_player_posy))
{
	//_actionSet = std::make_unique<ActionSet_t>();

	std::string actPath = "action/player.act";
	LoadAction(actPath);
	

	_updateFunc = &Player::NeutralUpdate;
	_vel = { 0,0 };
	_isAerial = false;
	_currentActionName = "idle";
	_frame = 0;
}


Player::~Player()
{
}

void Player::LoadAction(std::string & actPath)
{
	/*ActionData act;
	bool result = Application::Instance().GetFileSystem()->Load(actPath.c_str(), act);
	auto actdata = act.GetRawData();

	std::string imgFilePath = "";
	ActionData::BuildActionSet(act, *_actionSet, imgFilePath);
	imgFilePath = GetFolderPath(actPath) + imgFilePath;

	ImageData data;
	Application::Instance().GetFileSystem()->Load(imgFilePath.c_str(), data);
	_imgH = data.GetHandle();
*/

	int ActPath = FileRead_open(actPath.c_str());


	float version;
	FileRead_read(&version, sizeof(version), ActPath);

	int imgfilepathlen = 0;
	FileRead_read(&imgfilepathlen, sizeof(imgfilepathlen), ActPath);

	std::string imgFilePath;
	imgFilePath.resize(imgfilepathlen);
	FileRead_read(&imgFilePath[0], imgfilepathlen, ActPath);

	imgFilePath = GetFolderPath(actPath) + imgFilePath;
	ImageData data;
	Application::Instance().GetFileSystem()->Load(imgFilePath.c_str(), data);
	_imgH = data.GetHandle();

	int totalloop = 0;
	int actionCount = 0;
	FileRead_read(&actionCount, sizeof(actionCount), ActPath);
	for (int i = 0; i < actionCount; ++i) {
		int actionnamesize = 0;
		FileRead_read(&actionnamesize, sizeof(actionnamesize), ActPath);
		std::string actionname;
		actionname.resize(actionnamesize);
		FileRead_read(&actionname[0], actionnamesize, ActPath);

		FileRead_read(&totalloop, sizeof(totalloop), ActPath);
		int animcount = 0;
		FileRead_read(&animcount, sizeof(animcount), ActPath);
		std::vector<CutData> animcutinfoes(animcount);
		for (int i = 0; i < animcount; ++i) {
			FileRead_read(&animcutinfoes[i], sizeof(animcutinfoes[i]), ActPath);
		}
		_actionSet[actionname].cutdata = animcutinfoes;
	}
	FileRead_close(ActPath);


	/*int actioncnt = 0;
	FileRead_read(&actioncnt, sizeof(actioncnt), ActPath);
	for (int i = 0; 0 < actioncnt; i++)
	{
		CutData cd = {};
		Rect cutrect;
		Position2 center;
		int duration;

		int actionnamesize = 0;
		FileRead_read(&actionnamesize, sizeof(actionnamesize), ActPath);
		std::string actionname;
		actionname.resize(actionnamesize);
		FileRead_read(&actionname[0], actionnamesize, ActPath);
		int cutdataCount = 0;
		FileRead_read(&cutdataCount, sizeof(cutdataCount), ActPath);
		if (cutdataCount > 0)
		{

		}
		std::vector<CutData> animcutinfoes(actioncnt);
		for (int i = 0; i < actioncnt; ++i)
		{
			FileRead_read(&animcutinfoes[i], sizeof(animcutinfoes[i]), ActPath);
		}
		_actionSet[actionname].cutdata = animcutinfoes;
	}
	FileRead_close(ActPath);*/
}

void Player::Update(const Input & input)
{
	++_frame;
	(this->*_updateFunc)(input);
	for (int i = 0; i < GetJoypadNum() + 1; ++i)
	{

	}
	Move(_vel);
}

void Player::OnDead()
{

}

void Player::OnGround(float grad, float adjustY)
{
}

void Player::Draw()
{
	Position2 offset = _camera.GetOffset();
	DrawCircle(_pos.x - offset.x,_pos.y - offset.y,20,0xffffff,true,true);
	DrawRectRotaGraph2(_pos.x - offset.x, _pos.y - offset.y,
		_actionSet[_currentActionName].cutdata[_frame].cutrect.Left(),
		_actionSet[_currentActionName].cutdata[_frame].cutrect.Top(),
		_actionSet[_currentActionName].cutdata[_frame].cutrect.size.w,
		_actionSet[_currentActionName].cutdata[_frame].cutrect.size.h,
		_isLeft? 12:0,
		0,
		1.0f, 0.0f, _imgH, true,_isLeft);
}

void Player::Move(const Vector2f& move)
{
	_pos += move;
}

const Vector2f & Player::GetPosition() const
{
	return _pos;
}

void Player::NeutralUpdate(const Input & input)
{
	
	_vel *= 0.95f;
	if (input.Ispressed(0, "left"))
	{
		_isLeft = true;
		_updateFunc = &Player::RunUpdate;
	}
	if (input.Ispressed(0, "right"))
	{
		_isLeft = false;
		_updateFunc = &Player::RunUpdate;
	}
	
}

void Player::RunUpdate(const Input & input)
{
	if (input.Ispressed(0, "left"))
	{
		_isLeft = true;
		_vel.x -= 0.1f;
	}
	else if (input.Ispressed(0, "right"))
	{
		_isLeft = false;
		_vel.x += 0.1f;
	}
	else
	{
		_updateFunc = &Player::NeutralUpdate;
	}
}

void Player::JumpUpdate(const Input & input)
{
	Aerial();
	if (_frameOfJumpButtonPressing > 0)
	{
		if (input.Ispressed(0, "jump"))
		{
			++_frameOfJumpButtonPressing;
		}
		if (input.IsReleasd(0, "jump") || _frameOfJumpButtonPressing >= 10)
		{
			_vel.y = jump_power * static_cast<float>(_frameOfJumpButtonPressing);
				_frameOfJumpButtonPressing = 0;
		}
	}
	if (_pos.y <= _ground->GetCurrentGroundY(_grad))
	{
		_vel.y = 0;
		_isAerial = false;
		_updateFunc = &Player::NeutralUpdate;
	}
}

void Player::GroundUpdate(const Input &input )
{
}

void Player::DamageUpdate(const Input &input)
{

}

void Player::JumpCheck(const Input & input)
{
	if (input.Ispressed(0, "jump"))
	{
		_frameOfJumpButtonPressing = 1;
		_updateFunc = &Player::JumpUpdate;
	}
	
}

void Player::Jump()
{
	if (!_isAerial)
	{
		_vel.y = jump_power;
		_isAerial = true;
		_updateFunc = &Player::JumpUpdate;
	}
}

void Player::AdjustY(float grad, float adjustY)
{
	if (adjustY > 0.0f)
	{
		_pos.y = adjustY;
	}
	_angel = atanf(grad);
	//_gsin = _g*(grad/(1+grad * grad))
}

void Player::Aerial()
{
	_vel.y += g;
}

void Player::GetGroundP(std::shared_ptr<Ground> gp)
{
	_ground = gp;
}

const BoxCollider & Player::GetCollider() const
{
	return _collider;
}
