#include "Camera.h"
#include "../Application.h"
#include "Player.h"

Camera::Camera()
{
	_pos = { 0,0 };
}


Camera::~Camera()
{
}

void Camera::AddPlayer(std::shared_ptr<Player> player)
{
	_players.push_back(player);
}

void Camera::RemovePlayer(std::shared_ptr<Player> player)
{

}

void Camera::SetRange(const Size & stageSize)
{
}

void Camera::Update()
{
	Vector2f pPos;
	for (auto p : _players)
	{
		pPos = p->GetPosition();
	}
	_initPos = Position2(pPos.ToIntVec().x,pPos.ToIntVec().y);
	_pos = _initPos;
	
}

const Position2 & Camera::GetPosition() const
{
	return _pos;
}

const Rect & Camera::GetViewRange() const
{
	auto w = Application::Instance().GetConfig().GetScreenSize();
	Rect Range;
	Range.center = _pos;
	Range.size = w;
	return Range;
}

const Position2 & Camera::GetOffset() const
{
	auto w = Application::Instance().GetConfig().GetScreenSize();
	return  Position2((_pos.x - (w.w/2)),(_pos.y));
}
