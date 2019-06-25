#pragma once
#include <memory>
#include <string>
#include "Actor.h"
class Camera;

class Player :
	public Actor
{
public:
	Player(const Camera cam);
	~Player();
	void Update(const Input&)override final;
	void Draw()override final;
	void Move(const Vector2f& move);
private:
	unsigned int _frame;
	int _imgH;
	bool _isLeft;
	std::string _currentActionName = "";

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

