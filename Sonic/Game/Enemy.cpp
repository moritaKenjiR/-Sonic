#include "Enemy.h"
#include "Game/Camera.h"

Enemy::Enemy(const Camera& cam, const Player& player, const Position2f& pos) :_player(player),Actor(cam,pos)
{
	
}

Enemy::~Enemy()
{
}
