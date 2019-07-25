#include "Ant.h"


Ant::Ant(const Camera& cam,const Player & player,int  x,int y, const float speed):Enemy(cam,player,Position2f(x,y),speed)
{
	AimPlayer();
	_currentActionName = "idle";
	_currentIndex = 0;
	_collider.reset(new BoxCollider(_actionSet["idle"].cutdata[0].cutrect));
	_updater = &Ant::NormalUpdate;
}

Ant::~Ant()
{
}

void Ant::Update(const Input &)
{
}

void Ant::Draw()
{

}

void Ant::OnGround(float grad, float adjustY)
{
}

void Ant::OnDead()
{
}

std::shared_ptr<Enemy> Ant::MakeClone()
{
	return std::make_shared<Ant>(*this);
}
