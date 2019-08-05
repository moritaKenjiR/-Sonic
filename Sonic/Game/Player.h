#pragma once
#include <memory>
#include <string>
#include <map>
#include "Actor.h"
#include "action.h"
class Camera;
class GameScene;
class Ground;
class BoxCollider;


class Player :
	public Actor
{
	friend GameScene;
public:
	Player(const Camera& cam);
	~Player();
	void LoadAction(std::string& actPath);
	void Update(const Input&)override final;
	void OnDead()override final;
	void OnGround(float grad, float adjustY = -1.0f)override final;
	void Draw()override final;
	void Move(const Vector2f& move);
	const Vector2f& GetPosition()const;

	void NeutralUpdate(const Input&);
	void RunUpdate(const Input&);
	void JumpUpdate(const Input&);
	void DamageUpdate(const Input&);

	void JumpCheck(const Input&);
	void Jump();
	void AdjustY(float grad,float adjustY);
	void Aerial();
	void GetGroundP(std::shared_ptr<Ground> gp);

	 BoxCollider& GetCollider();

	
private:
	void (Player::*_updateFunc)(const Input&);
	unsigned int _frame;
	int _imgH;
	
	
	std::shared_ptr<Ground> _ground;

	float _accel;
	float _framerate;
	float _grad;
	float _angel;
	bool _isAerial;
	float _jumpPower;
	int _frameOfJumpButtonPressing;
	int _jumpSE;

	//std::map<std::string, Action> _actionData;
};


