#pragma once
#include "../Geometry.h"
#include "action.h"
#include <string>
#include "../Collision.h"
class Input;
class Camera;
class BoxCollider;

//「ｹﾞｰﾑ中に動くもの」基底ｸﾗｽ
class Actor
{
public:
	Actor(const Camera& cam);
	Actor(const Camera& cam, const Position2f& pos);
	virtual ~Actor();
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;

	virtual void OnGround(float grad, float adjustY = -1.0f)= 0;
	virtual void OnDead() = 0;

	virtual bool IsDie();

	virtual void Move(float x, float y);
	virtual void Move(const Vector2f& vec);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Position2f& vec);
	virtual const Position2f& GetPosition()const;

	virtual const Vector2f& GetVelocity()const;
	virtual void SetVelocity(const Vector2f& vel);

	virtual const BoxCollider& GetCollider()const;
private:

protected:
	ActionSet_t _actionSet;
	BoxCollider _collider;
	virtual void LoadAction(std::string &actpath);
	Position2f _pos;
	Vector2f _vel;
	const Camera& _camera;
	std::string _currentActionName = "";
	int atlasImageH;
	int _currentIndex = 0;
	unsigned int _frame = 0;
	bool _isAvailable;
	bool _isLeft;
};

