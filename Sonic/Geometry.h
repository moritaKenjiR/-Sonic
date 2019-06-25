#pragma once


struct Size
{
	int w, h;
};
struct Position2
{
	int x, y;
	Position2() {}
	Position2(int inx, int iny) { x = inx; y = iny; }
};

struct Position2f
{
	float x, y;
};

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

Vector2f operator+(const Vector2f& lval, const Vector2f& rval);
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
	Rect();
	Rect(int x, int y, int w, int h);
	Rect(Position2& pos, Size& sz);
};