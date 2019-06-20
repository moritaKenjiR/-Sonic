#include "Player.h"
#include <DxLib.h>
#include "../Input/Input.h"
#include "Camera.h"

constexpr int default_player_posx = 512;
constexpr int default_player_posy = 500;

Player::Player(const Camera cam):Actor(cam,Vector2f(default_player_posx,default_player_posy))
{
	_imgH = LoadGraph("Image/player.png", true);
}


Player::~Player()
{
}

void Player::Update(const Input & _input)
{
	for (int i = 0; i < GetJoypadNum() + 1; ++i)
	{
		if (_input.Ispressed(i, "left"))
		{
			_isLeft = true;
			Move(Vector2f(-5, 0));
		}
		if (_input.Ispressed(i, "right"))
		{
			_isLeft = false;
			Move(Vector2f(5, 0));
		}
		if (_input.Ispressed(i, "up"))
		{
			Move(Vector2f(0, -5));
		}
		if (_input.Ispressed(i, "down"))
		{
			Move(Vector2f(0, 5));
		}
	}
}

void Player::Draw()
{
	DrawRectRotaGraph(_pos.x, _pos.y, 0, 100, 27, 27, 2.0f, 0.0f, _imgH, true,_isLeft);
}

void Player::Move(const Vector2f& move)
{
	_pos += move;
}
