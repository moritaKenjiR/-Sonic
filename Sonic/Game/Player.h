#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Actor.h"
class Camera;
class GameScene;
class Ground;

class Player :
	public Actor
{
	friend GameScene;
public:
	Player(const Camera& cam);
	~Player();
	void Update(const Input&)override final;
	void Draw()override final;
	void Move(const Vector2f& move);
	const Vector2f& GetPosition()const;

	void NeutralUpdate(const Input&);
	void RunUpdate(const Input&);
	void JumpUpdate(const Input&);
	void GroundUpdate(const Input&);
	void DamageUpdate(const Input&);

	void Jump();
	void AdjustY(float grad,float adjustY);
	void Aerial();
	void GetGroundP(std::shared_ptr<Ground> gp);
private:
	void (Player::*_updateFunc)(const Input&);
	unsigned int _frame;
	int _imgH;
	bool _isLeft;
	std::string _currentActionName = "";
	std::shared_ptr<Ground> _ground;

	Vector2f _vel;
	float _accel;
	float _framerate;
	float _grad;
	float _angel;
	bool _isAerial;
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

