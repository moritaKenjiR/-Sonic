#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "Actor.h"
class Camera;
class GameScene;
class Ground;
class BoxCollider;
struct Action;

struct ActionSet {
	std::map<std::string, Action> actions;
};

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
	void Draw()override final;
	void Move(const Vector2f& move);
	const Vector2f& GetPosition()const;

	void NeutralUpdate(const Input&);
	void RunUpdate(const Input&);
	void JumpUpdate(const Input&);
	void GroundUpdate(const Input&);
	void DamageUpdate(const Input&);

	void JumpCheck(const Input&);
	void Jump();
	void AdjustY(float grad,float adjustY);
	void Aerial();
	void GetGroundP(std::shared_ptr<Ground> gp);

	const BoxCollider& GetCollider()const;

	enum class HitRectType {
		none,
		attack,
		damage,
		push,
	};
private:
	void (Player::*_updateFunc)(const Input&);
	unsigned int _frame;
	int _imgH;
	bool _isLeft;
	std::string _currentActionName = "";
	std::shared_ptr<Ground> _ground;
	std::unique_ptr<ActionSet> _actionSet;

	Vector2f _vel;
	float _accel;
	float _framerate;
	float _grad;
	float _angel;
	bool _isAerial;
	float _jumpPower;
	int _frameOfJumpButtonPressing;

	struct ActionRect {
		HitRectType type;
		Rect rc;
	};

	struct CutData {
		Rect cutrect;
		Position2 center;
		int duration;
		std::vector<ActionRect> actrect;
	};

	struct Action {
		char isLoop;
		std::vector<CutData> cutdata;
		unsigned int totalDuration;
	};

	std::map<std::string, Action> _actionData;
};


