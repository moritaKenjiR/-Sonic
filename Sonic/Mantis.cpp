#include "Mantis.h"



Mantis::Mantis(const Camera& cam, const Player& player, int x, int y) :Enemy(cam, player, Position2f(x, y))
{
}


Mantis::~Mantis()
{
}

void Mantis::Update(const Input &)
{
}

void Mantis::Draw()
{
}

void Mantis::OnGround(float grad, float adjustY)
{
}

void Mantis::OnDead()
{
}
