#pragma once
#include "Geometry.h"

class BoxCollider;

class Collider
{
public:
	Collider();
	~Collider();
	static bool IsCollided(const BoxCollider& a, const BoxCollider& b);
};

class BoxCollider : public Collider
{
private:
	Rect _rect;
public:
	BoxCollider(const Rect& rc): _rect(rc) {}
	const Rect& GetRect()const;
	void SetRect(const Rect& rc);
};

