#pragma once
#include "../Geometry.h"
class Input;
class Camera;

//「ｹﾞｰﾑ中に動くもの」基底ｸﾗｽ
class Actor
{
public:
	Actor(const Camera cam);
	Actor(const Camera cam, const Vector2f& pos);
	virtual ~Actor();
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;
private:

protected:
	Vector2f _pos;
	const Camera& _camera;
};

