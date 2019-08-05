#include "Actor.h"
#include "Camera.h"


Actor::Actor(const Camera& cam):_camera(cam), _pos(0,0), _collider(Rect(Position2(0,0), Size(32, 32)))
{
}

Actor::Actor(const Camera& cam,const Position2f & pos):_camera(cam),_pos(pos),_collider(Rect(pos.ToIntVec(),Size(32,32)))
{
}

Actor::~Actor()
{
}

void Actor::LoadAction(std::string & actPath)
{
}

bool Actor::IsDie()
{
	return !_isAvailable;
}

void Actor::Move(float x, float y)
{
}

void Actor::Move(const Vector2f & vec)
{
	_pos += vec;
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

const BoxCollider & Actor::GetCollider() const
{
	return _collider;
}
