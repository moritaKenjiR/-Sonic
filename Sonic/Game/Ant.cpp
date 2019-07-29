#include "Ant.h"

constexpr int antspeed = 4;

Ant::Ant(const Camera& cam,const Player & player,int  x,int y):Enemy(cam,player,Position2f(x,y),antspeed)
{
	AimPlayer();
	_currentActionName = "idle";
	_currentIndex = 0;
	_collider = _actionSet["idle"].cutdata[0].cutrect;
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

void Ant::NormalUpdate()
{
}

std::shared_ptr<Enemy> Ant::MakeClone()
{
	auto ret = std::make_shared<Ant>(*this);
	ret->_isAvailable = true;
	return ret;
}
