#include "Mantis.h"

constexpr int mantisspeed = 3;

Mantis::Mantis(const Camera& cam, const Player& player, int x, int y) :Enemy(cam, player, Position2f(x, y), mantisspeed)
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

std::shared_ptr<Enemy> Mantis::MakeClone()
{
	return std::make_shared<Mantis>(*this);
}
