#include "Collision.h"



Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::IsCollided(const BoxCollider & a, const BoxCollider & b)
{
	return false;
}

const Rect & BoxCollider::GetRect() const
{
	return _rect;
}
