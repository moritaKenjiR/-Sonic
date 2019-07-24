#pragma once
#include "Enemy.h"
class Ant :
	public Enemy
{
public:
	Ant(const Camera& cam, const Player& player,int x, int y);
	~Ant();

	void Update(const Input&)override final;
	void Draw()override final;

	void OnGround(float grad, float adjustY = -1.0f)override final;
	void OnDead()override final;

	std::shared_ptr<Enemy> MakeClone()override final;
private:
	Vector2f _vel;
};

