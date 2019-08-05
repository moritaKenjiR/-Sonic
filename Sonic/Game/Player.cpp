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

constexpr int default_player_posx = 100;
constexpr int default_player_posy = 100;
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
	_jumpSE = LoadSoundMem("se/jump.wav");
	_frame = 0;
}


Player::~Player()
{
}

void Player::LoadAction(std::string & actPath)
{
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

	int actionCount = 0;
	FileRead_read(&actionCount, sizeof(actionCount), ActPath);
	for (int i = 0; i < actionCount; ++i) {
		int actionnamesize = 0;
		FileRead_read(&actionnamesize, sizeof(actionnamesize), ActPath);
		std::string actionname;
		actionname.resize(actionnamesize);
		FileRead_read(&actionname[0], actionnamesize, ActPath);

		char loop;
		FileRead_read(&loop, sizeof(loop), ActPath);
		_actionSet[actionname].isLoop = loop;
		int cutdatacount = 0;
		FileRead_read(&cutdatacount, sizeof(cutdatacount), ActPath);
		for (int j = 0; j < cutdatacount; ++j)
		{
			CutData cd = {};
			Rect cutrect;
			Position2 center; 
			int duration;

			FileRead_read(&cd.cutrect, sizeof(cd.cutrect), ActPath);
			FileRead_read(&cd.center, sizeof(cd.center), ActPath);
			FileRead_read(&cd.duration, sizeof(cd.duration), ActPath);

			int actcount = 0;
			FileRead_read(&actcount, sizeof(actcount), ActPath);
			if (actcount > 0) {
				cd.actrects.resize(actcount);
				for (auto& actrect : cd.actrects) {
					FileRead_read(&actrect, sizeof(actrect), ActPath);
				}
			}
			_actionSet[actionname].cutdata.emplace_back(cd);
			_actionSet[actionname].totalDuration += cd.duration;
		}
	}
	FileRead_close(ActPath);
}

void Player::Update(const Input & input)
{
	++_frame;
	_collider.GetRect().center = _pos.ToIntVec() + Position2(-50,-92);
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
	if (_frame >= _actionSet[_currentActionName].totalDuration) _frame = 0;
	Position2 offset = _camera.GetOffset();
	DrawRectRotaGraph2(_collider.GetRect().center.x - offset.x, _collider.GetRect().center.y - offset.y,
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.Left(),
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.Top(),
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.size.w,
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.size.h,
		_isLeft? 0:0,
		0,
		4.0f, _angel, _imgH, true,_isLeft);
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
	_currentActionName = "idle";
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

	if (input.Ispressed(0, "jump"))
	{
		Jump();
	}
	if (abs(_pos.y - _ground->GetCurrentGroundY(_grad)) > 4)
	{
		_isAerial = true;
		_updateFunc = &Player::JumpUpdate;
	}
	{
		AdjustY(_grad, _ground->GetCurrentGroundY(_grad));
	}
}

void Player::RunUpdate(const Input & input)
{
	if (abs(_pos.y - _ground->GetCurrentGroundY(_grad)) > 8)
	{
		_isAerial = true;
		_updateFunc = &Player::JumpUpdate;
	}
	{
		AdjustY(_grad, _ground->GetCurrentGroundY(_grad));
	}
	_currentActionName = "run";
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
	else if (input.Ispressed(0, "jump"))
	{
		Jump();
	}
	else
	{
		_updateFunc = &Player::NeutralUpdate;
	}
}

void Player::JumpUpdate(const Input & input)
{
	_currentActionName = "jump";
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
	if (abs(_pos.y - _ground->GetCurrentGroundY(_grad)) < 10)
	{
		_vel.y = 0;
		_isAerial = false;
		_updateFunc = &Player::NeutralUpdate;
	}
}

void Player::DamageUpdate(const Input &input)
{
	_currentActionName = "damage";
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
	PlaySoundMem(_jumpSE, DX_PLAYTYPE_BACK);
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

 BoxCollider & Player::GetCollider() 
{
	return _collider;
}
