#pragma once
#include "Geometry.h"

class BoxCollider;

class Collider
{
public:
	Collider();
	~Collider();
	static bool IsCollided( BoxCollider& a,  BoxCollider& b);
};

class BoxCollider : public Collider
{
private:
	Rect _rect;
public:
	BoxCollider(const Rect& rc): _rect(rc) {}
	Rect& GetRect();
	void SetRect(const Rect& rc);
};

