#pragma once
#include "Enemy.h"
class Ant :
	public Enemy
{
public:
	Ant(const Player& player,int x, int y);
	~Ant();

	void Update()override final;
	void Draw()override final;
private:
	Vector2f _vel;
};

