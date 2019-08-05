#pragma once
#include "Event.h"
#include "../Geometry.h"
#include "../Collision.h"
class Camera;

class Coin :
	public Event
{
public:
	Coin(const Camera& cam,const Position2& pos, EventQueue& eventq);
	~Coin();
	EventType GetType()const override final;
	void Update()override final;
	void Draw()override final;
	 BoxCollider& GetCollider();
	void OnCollision(Actor* actor, const BoxCollider& col);
private:
	int _imgH;
	const Camera& _camera;
	BoxCollider _bc;
	int _coinSE;
};

