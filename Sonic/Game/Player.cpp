#include "Player.h"
#include <DxLib.h>
#include <string>
#include "../Input/Input.h"
#include "Camera.h"
#include <casetup.h>

constexpr int default_player_posx = 512;
constexpr int default_player_posy = 500;

Player::Player(const Camera cam):Actor(cam,Vector2f(default_player_posx,default_player_posy))
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

	}
	FileRead_close(playerActPath);
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
