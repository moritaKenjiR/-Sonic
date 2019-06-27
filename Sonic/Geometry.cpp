#include "Geometry.h"
#include <cmath>
#include <DxLib.h>

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

Position2 operator*(const Position2 & lval, const float scale)
{
	return Position2((int)(lval.x * scale),(int)( lval.y * scale));
}

Position2 operator-(const Position2 & lval, const Position2 & rval)
{
	return Position2(lval.x - rval.x, lval.y - rval.y);
}

bool operator!=(const Position2 & lval, const Position2 & rval)
{
	if ((lval.x != rval.x) || (lval.y != rval.y))
	{
		return true;
	}
	return false;
}



///ãÈå`ç\ë¢ëÃ
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

void Segment::Draw(unsigned int color)
{
	DrawLine(posa.x, posa.y, posb.x, posb.y, color, true);
}

Position2 Position2::operator-()
{
	return Position2(-x,-y);
}
