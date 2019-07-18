#pragma once
#include "Geometry.h"
#include "Game/Actor.h"
#include "Game/Camera.h"
class Player;
class Camera;

class Enemy : public Actor
{
protected:
	const Player& _player;
public:
	Enemy(const Camera& cam, const Player& player,const Position2f& pos);
	virtual ~Enemy();

	virtual void Update(const Input&) override = 0;
	virtual void Draw() override = 0;

	virtual void OnGround(float grad, float adjustY = -1.0f)override = 0;
	virtual void OnDead()override = 0;

};

