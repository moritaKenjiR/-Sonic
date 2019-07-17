#pragma once
#include "Geometry.h"
class Player;

class Enemy
{
public:
	Enemy(const Player& player);
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	const Player& _player;
	Position2f _pos;
};

