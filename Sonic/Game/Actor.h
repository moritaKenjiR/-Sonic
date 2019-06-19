#pragma once
#include "../Geometry.h"
class Input;

//「ｹﾞｰﾑ中に動くもの」基底ｸﾗｽ
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

