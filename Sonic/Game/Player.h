#pragma once
#include <memory>
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
	int _imgH;
	bool _isLeft;
	//std::unique_ptr<Camera> _camera;
};

