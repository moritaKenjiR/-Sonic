#include "Enemy.h"
#include "../Game/Camera.h"

Enemy::Enemy(const Camera& cam, const Player& player, const Position2f& pos) :_player(player),Actor(cam,pos)
{
	
}

Enemy::~Enemy()
{
}

void Enemy::OnCollision(Actor & actor)
{
	auto v = actor.GetVelocity();
	if (pos.y > actor.GetPosition().y && v.y > 0)
	{
		PlaySoundMem();
		actor.SetVelocity(0,-15.0f);
		OnDead();
	}
	else
	{
		ac
	}
}
