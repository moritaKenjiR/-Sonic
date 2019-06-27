#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Actor.h"
class Camera;

class Player :
	public Actor
{
public:
	Player(const Camera cam);
	~Player();
	void Update( Input&)override final;
	void Draw()override final;
	void Move(const Vector2f& move);
	const Vector2f& GetPosition()const;

	void NeutralUpdate(Input&);
	void RunUpdate(Input&);
	void JumpUpdate(Input&);
	void GroundUpdate(Input&);
	void DamageUpdate(Input&);

	void Jump();
	void AdjustY(float grad,float adjustY);
	void Aerial();
private:
	void (Player::*_updateFunc)(Input&);
	unsigned int _frame;
	int _imgH;
	bool _isLeft;
	std::string _currentActionName = "";

	Vector2f _vel;
	float accel;
	float framerate;
	struct CutData {
		Rect cutrect;
		Position2 center;
		int duration;
		int actrccnt;
	};

	struct Action {
		char isLoop;
		std::vector<CutData> cutdata;
		unsigned int totalDuration;
	};
};

