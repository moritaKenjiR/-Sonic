#include "Player.h"
#include <DxLib.h>
#include <math.h>
#include <string>
#include "../Input/Input.h"
#include "Camera.h"
#include "../scene/GameScene.h"
#include"../Ground.h"

constexpr int default_player_posx = 512;
constexpr int default_player_posy = 500;
constexpr float jump_power = -10.0f;
constexpr float g = 0.3f;

Player::Player(const Camera& cam):Actor(cam,Vector2f(default_player_posx,default_player_posy))
{
	_imgH = LoadGraph("img/player.png", true);

	std::string actPath = "action/player.act";
	int playerActPath = FileRead_open(actPath.c_str());


	float version;
	FileRead_read(&version, sizeof(version), playerActPath);

	int imgfilepathlen = 0;
	FileRead_read(&imgfilepathlen, sizeof(imgfilepathlen), playerActPath);

	std::string imgfilepath;
	imgfilepath.resize(imgfilepathlen);
	FileRead_read(&imgfilepath[0], imgfilepathlen, playerActPath);

	auto slash = actPath.find_last_of('/');
	imgfilepath = actPath.substr(0, slash + 1) + imgfilepath;

	int actioncnt = 0;
	FileRead_read(&actioncnt, sizeof(actioncnt), playerActPath);
	for (int i = 0; 0 < actioncnt; i++)
	{
		int actionnamesize = 0;
		FileRead_read(&actionnamesize, sizeof(actionnamesize), playerActPath);
		std::string actionname;
		actionname.resize(actionnamesize);
		FileRead_read(&actionname[0], actionnamesize, playerActPath);
		actioncnt = 0;
		FileRead_read(&actioncnt, sizeof(actioncnt), playerActPath);
		std::vector<CutData> animcutinfoes(actioncnt);
		for (int i = 0; i < actioncnt; ++i)
		{
			FileRead_read(&animcutinfoes[i], sizeof(animcutinfoes[i]), playerActPath);
		}
		_actionData[actionname].cutdata = animcutinfoes;
	}
	FileRead_close(playerActPath);

	_updateFunc = &Player::NeutralUpdate;
	_vel = { 0,0 };
	_isAerial = false;
}


Player::~Player()
{
}

void Player::Update(const Input & input)
{
	(this->*_updateFunc)(input);
	for (int i = 0; i < GetJoypadNum() + 1; ++i)
	{

	}
	Move(_vel);
}

void Player::Draw()
{
	Position2 offset = _camera.GetOffset();
	DrawCircle(_pos.x - offset.x,_pos.y - offset.y,20,0xffffff,true,true);
	DrawRectRotaGraph(_pos.x, _pos.y, 0, 100, 27, 27, 2.0f, 0.0f, _imgH, true,_isLeft);
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
