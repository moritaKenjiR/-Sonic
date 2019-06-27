#include "Player.h"
#include <DxLib.h>
#include <math.h>
#include <string>
#include "../Input/Input.h"
#include "Camera.h"
#include <casetup.h>

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
	FileRead_read(&version, sizeof(version),playerActPath);

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
		break;
	}
	FileRead_close(playerActPath);

	_updateFunc = &Player::NeutralUpdate;
	_vel = { 0,0 };
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
	if (input.Ispressed(0, "up"))
	{
		Jump();
		_updateFunc = &Player::JumpUpdate;
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
	_vel.y += g;
	if (_pos.y > 500)
	{
		_vel.y = 0;
		_updateFunc = &Player::NeutralUpdate;
	}
}

void Player::GroundUpdate(const Input &input )
{
}

void Player::DamageUpdate(const Input &input)
{

}

void Player::Jump()
{
	_vel.y = jump_power;
}

void Player::AdjustY(float grad, float adjustY)
{
	if (adjustY > 0.0f)
	{
		_pos.y = adjustY;
	}
	//_angel = atanf(grad);
	//_gsin = _g*(grad/(1+grad * grad))
}

void Player::Aerial()
{
}
