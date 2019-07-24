#pragma once
#include "../Geometry.h"
#include "Actor.h"
#include "Camera.h"
class Player;
class Camera;
class Spawner;

class Enemy : public Actor
{
	friend Spawner;
private:
	virtual std::shared_ptr<Enemy> MakeClone() = 0;
protected:
	const Player& _player;
public:
	Enemy(const Camera& cam, const Player& player,const Position2f& pos);
	virtual ~Enemy();

	virtual void Update(const Input&) override = 0;
	virtual void Draw() override = 0;

	virtual void OnGround(float grad, float adjustY = -1.0f)override = 0;
	virtual void OnDead()override = 0;
	virtual void OnCollision(Actor& actor);
};

