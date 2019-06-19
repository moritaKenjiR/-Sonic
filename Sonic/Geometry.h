#pragma once

struct Position2
{
	int x, y;
};

struct Position2f
{
	float x, y;
	Position2f(){}
	Position2f(float inx, float iny) { x = inx; y = iny; }
};

struct Size
{
	int w, h;
};