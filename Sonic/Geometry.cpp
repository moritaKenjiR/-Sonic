#include "Geometry.h"
#include <cmath>

Vector2f Vector2f::operator-()
{
	return Vector2f(-x, -y);
}

void Vector2f::operator+=(const Vector2f & in)
{
	x += in.x;
	y += in.y;
}

void Vector2f::operator-=(const Vector2f & in)
{
	x -= in.x;
	y -= in.y;
}

void Vector2f::operator*=(float scale)
{
	x *= scale;
	y *= scale;
}

void Vector2f::operator/=(float scale)
{
	x /= scale;
	y /= scale;
}

Vector2 Vector2f::ToIntVec() const
{
	Vector2 v = { (int)x,(int)y };
	return v;
}

float Vector2f::Magnitude() const
{
	return hypot(x, y);
}

Vector2f Vector2f::Normalized() const
{
	auto len = Magnitude();
	return Vector2f(x / len, y / len);
}


Vector2f operator+(const Vector2f & lval, const Vector2f & rval)
{
	return Vector2f(lval.x + rval.x, lval.y + rval.y);
}

Vector2f operator-(const Vector2f & lval, const Vector2f & rval)
{
	return Vector2f(lval.x - rval.x, lval.y - rval.y);
}

Vector2f operator*(const Vector2f & lval, const float scale)
{
	return Vector2f(lval.x * scale, lval.y * scale);
}

Vector2f operator/(const Vector2f & lval, const float scale)
{
	return Vector2f(lval.x / scale, lval.y / scale);
}



///ãÈå`ç\ë¢ëÃ
Rect::Rect()
{
}

Rect::Rect(int x, int y, int w, int h)
{
	center = { x,y };
	size = { w,h };
}

Rect::Rect(Position2 & pos, Size & sz)
{
	center = pos;
	size = sz;
}
