#pragma once
#include "../Geometry.h"
#include "Actor.h"
#include "Camera.h"
class Player;
class Camera;
class Spawner;
class Ground;
class EventQueue;

class Enemy : public Actor
{
	friend Spawner;
private:
	virtual std::shared_ptr<Enemy> MakeClone() = 0;
	int _deathSE;
protected:
	const Player& _player;
	const Ground& _ground;
	const EventQueue& _eventQueue;
	const float _speed;
	
public:
	bool _isAvailable = false;
	Enemy(const Camera& cam, const Player& player,const Ground& ground, EventQueue& eventq,const Position2f& pos,const float speed);
	virtual ~Enemy();

	virtual void Update(const Input&) override = 0;
	virtual void Draw() override = 0;

	virtual void OnGround(float grad, float = -1.0f)override = 0;
	virtual void OnDead()override = 0;
	virtual void OnCollision(Actor& actor);

	virtual void AimPlayer();
};

