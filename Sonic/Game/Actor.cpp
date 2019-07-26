#include "Actor.h"
#include "Camera.h"


Actor::Actor(const Camera& cam):_camera(cam)
{
}

Actor::Actor(const Camera& cam,const Vector2f & pos):_camera(cam),_pos(pos)
{
}

Actor::~Actor()
{
}

void Actor::LoadAction(std::string & actPath)
{
}

void Actor::Move(float x, float y)
{
}

void Actor::Move(const Vector2f & vec)
{
}

void Actor::SetPosition(float x, float y)
{
	_pos = Vector2f(x, y);
}

void Actor::SetPosition(const Position2f & vec)
{
	_pos = vec;
}

const Position2f & Actor::GetPosition() const
{
	return _pos;
}


const Vector2f & Actor::GetVelocity() const
{
	return _vel;
}

void Actor::SetVelocity(const Vector2f & vel)
{
	_vel = vel;
}

const Rect & Actor::GetCollider() const
{
	return _collider;
}
