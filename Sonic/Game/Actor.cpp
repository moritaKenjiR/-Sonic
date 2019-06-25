#include "Actor.h"
#include "Camera.h"


Actor::Actor(const Camera cam):_camera(cam)
{
}

Actor::Actor(const Camera cam,const Vector2f & pos):_camera(cam),_pos(pos)
{
}


Actor::~Actor()
{
}

void Actor::Move(float x, float y)
{
	_pos += Vector2f(x, y);
}

void Actor::Move(const Vector2f & vec)
{
	_pos += vec;
}

void Actor::SetPosition(float x, float y)
{
	_pos = Vector2f(x, y);
}

void Actor::SetPosition(const Vector2f & vec)
{
	_pos = vec;
}

const Vector2f & Actor::GetPosition() const
{
	return _pos;
}
