#pragma once
#include "../Geometry.h"
class Input;

//u¹Ş°Ñ’†‚É“®‚­‚à‚ÌvŠî’ê¸×½
class Actor
{
public:
	Actor();
	Actor(const Position2f& pos);
	virtual ~Actor();
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;
private:

protected:
	Position2f _pos;
};

