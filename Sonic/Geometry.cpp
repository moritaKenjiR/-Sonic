#include "Geometry.h"
#include <cmath>
#include <DxLib.h>

Position2f Position2f::operator-()
{
	return Position2f(-x, -y);
}

void Position2f::operator+=(const Position2f & in)
{
	x += in.x;
	y += in.y;
}

void Position2f::operator-=(const Position2f & in)
{
	x -= in.x;
	y -= in.y;
}

void Position2f::operator*=(float scale)
{
	x *= scale;
	y *= scale;
}

void Position2f::operator/=(float scale)
{
	x /= scale;
	y /= scale;
}

Position2 Position2f::ToIntVec() const
{
	Position2 v = { (int)x,(int)y };
	return v;
}

float Position2f::Magnitude() const
{
	return hypot(x, y);
}

Position2f Position2f::Normalized() const
{
	auto len = Magnitude();
	return Position2f(x / len, y / len);
}


Position2f operator+(const Position2f & lval, const Position2f & rval)
{
	return Position2f(lval.x + rval.x, lval.y + rval.y);
}

Position2f operator-(const Position2f & lval, const Position2f & rval)
{
	return Position2f(lval.x - rval.x, lval.y - rval.y);
}


Position2f operator*(const Position2f & lval, const float scale)
{
	return Position2f(lval.x * scale, lval.y * scale);
}

Position2f operator/(const Position2f & lval, const float scale)
{
	return Position2f(lval.x / scale, lval.y / scale);
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

float Dot(const Vector2f & lval, const Vector2f & rval)
{
	return lval.x*rval.x + lval.y*rval.y;
}

float Cross(const Vector2f & lval, const Vector2f & rval)
{
	return lval.x*rval.y - lval.y*rval.x;
}



///ãÈå`ç\ë¢ëÃ
Rect::Rect(int x, int y, int w, int h)
{
	center = { x,y };
	size = { w,h };
}

Size Rect::OverlapSize(const Rect & rcA, const Rect & rcB)
{
	Size ret;
	ret.w = min(rcA.Right(), rcB.Right()) - max(rcA.Left(), rcB.Left());
	ret.h = min(rcA.Bottom(), rcB.Bottom()) - max(rcA.Top(), rcB.Top());
	return ret;
}

bool Rect::IsHit(const Rect & rcA, const Rect & rcB)
{
	return abs(rcA.center.x - rcB.center.x) < (rcA.size.w + rcB.size.w) / 2 &&
						abs(rcA.center.y - rcB.center.y) <= (rcA.size.h + rcB.size.h) / 2;
}


void Segment::Draw(unsigned int color)
{
	DrawLine(posa.x, posa.y, posb.x, posb.y, color, true);
}

Position2 Position2::operator-()
{
	return Position2(-x,-y);
}

Position2f Position2::ToFloatVec() const
{
	Position2f fpos = { (float)x,(float)y };
	return fpos;
}
