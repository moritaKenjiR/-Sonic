#pragma once


struct Size
{
	int w, h;
	Size() {}
	Size(int inw, int inh) { w = inw; h = inh; }
};

struct Position2;

struct Position2f
{
	float x, y;
	Position2f() {}
	Position2f(float inx, float iny) { x = inx; y = iny; }

	Position2f operator-();
	void operator+=(const Position2f& in);
	void operator-=(const Position2f& in);
	void operator*=(float scale);
	void operator/=(float scale);

	Position2 ToIntVec()const;
	float Magnitude()const;
	Position2f Normalized()const;
};

struct Position2
{
	int x, y;
	Position2() {}
	Position2(int inx, int iny) { x = inx; y = iny; }

	Position2 operator-();

	Position2f ToFloatVec()const;
};

using Vector2 = Position2;
using Vector2f = Position2f;

/*
struct Vector2
{
	int x, y;
	Vector2() {}
	Vector2(int inx, int iny) { x = inx; y = iny; }
};

struct Vector2f
{
	float x, y;
	Vector2f(){}
	Vector2f(float inx, float iny) { x = inx; y = iny; }

	Vector2f operator-();
	void operator+=(const Vector2f& in);
	void operator-=(const Vector2f& in);
	void operator*=(float scale);
	void operator/=(float scale);

	Vector2 ToIntVec()const;
	float Magnitude()const;
	Vector2f Normalized()const;
};
*/

Vector2f operator+(const Vector2f& lval, const Vector2f& rval);
Position2f operator-(const Position2f& lval, const Position2f& rval);
Vector2f operator-(const Vector2f& lval, const Vector2f& rval);
Vector2f operator*(const Vector2f& lval, const float scale);
Vector2f operator/(const Vector2f& lval, const float scale);

Position2 operator*(const Position2& lval, const float scale);
Position2 operator-(const Position2& lval, const Position2& rval);
bool operator!=(const Position2& lval, const Position2& rval);


struct Rect
{
	Position2 center;
	Size size;
	Rect() {};
	Rect(int x, int y, int w, int h);
	Rect(Position2 pos, Size sz) :center(pos), size(sz) {};

	const int Left()const { return center.x - size.w / 2; };
	const int Right()const { return center.x + size.w / 2; };
	const int Top()const { return center.y - size.h / 2; };
	const int Bottom()const { return center.y + size.h / 2; };

	static Size OverlapSize(const Rect& rcA, const Rect& rcB);
	static bool IsHit(const Rect& rcA, const Rect& rcB);
};

struct Segment {
	Position2f posa;
	Position2f posb;
	Segment() {}
	Segment(const Position2f& a, const Position2f& b) { posa = a; posb = b; }
	Segment(float ax, float ay, float bx, float by) { posa = Position2f(ax, ay); posb = Position2f(bx, by); };
	void Draw(unsigned int color = 0xffffffff);
};