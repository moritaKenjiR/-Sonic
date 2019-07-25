#include "Enemy.h"
#include <DxLib.h>
#include "../Game/Camera.h"


Enemy::Enemy(const Camera& cam, const Player& player, const Position2f& pos, const float speed) :_player(player),Actor(cam,pos),_speed(speed)
{
	
}


Enemy::~Enemy()
{
}

void Enemy::OnCollision(Actor & actor)
{
	auto v = actor.GetVelocity();
	if (_pos.y > actor.GetPosition().y && v.y > 0)
	{
		PlaySoundMem(_deathSE,DX_PLAYTYPE_BACK);
		actor.SetVelocity(Vector2f(0,-15.0f));
		OnDead();
	}
	else
	{
		
	}
}

void Enemy::AimPlayer()
{
}
