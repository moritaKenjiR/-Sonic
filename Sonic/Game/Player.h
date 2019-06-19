#pragma once
#include "Actor.h"
class Player :
	public Actor
{
public:
	Player();
	~Player();
	void Update(const Input&)override final;
	void Draw()override final;
	void Move(float x, float y);
private:
	int _imgH;
	bool _isLeft;
};

