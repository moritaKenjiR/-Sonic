#include "Ant.h"


Ant::Ant(const Camera& cam,const Player & player,int  x,int y):Enemy(cam,player,Position2f(x,y))
{

}

Ant::~Ant()
{
}

void Ant::Update(const Input &)
{
}

void Ant::Draw()
{

	DrawRectRotaGraph();
}

void Ant::OnGround(float grad, float adjustY)
{
}

void Ant::OnDead()
{
}
