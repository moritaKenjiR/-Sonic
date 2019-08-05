#include "Collision.h"
#include <cmath>


Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::IsCollided(BoxCollider & a, BoxCollider & b)
{
	auto acol = a.GetRect();
	auto bcol = b.GetRect();

	
	if ((abs(acol.center.x - bcol.center.x) < (acol.size.w + bcol.size.w)) &&
		(abs(acol.center.y - bcol.center.y) < (acol.size.h + bcol.size.h)))
	{
		return true;
	}
	return false;
}

 Rect & BoxCollider::GetRect() 
{
	return _rect;
}

void BoxCollider::SetRect(const Rect & rc)
{
	_rect = rc;
}
