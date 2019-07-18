#pragma once
#include "Enemy.h"
class Mantis :
	public Enemy
{
public:
	Mantis(const Camera& cam, const Player& player, int x, int y);
	~Mantis();

	void Update(const Input&)override final;
	void Draw()override final;

	void OnGround(float grad, float adjustY = -1.0f)override final;
	void OnDead()override final;
private:
	Vector2f _vel;
};

