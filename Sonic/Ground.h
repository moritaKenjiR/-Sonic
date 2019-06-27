#pragma once
#include "Geometry.h"

class Ground
{
public:
	Ground();
	~Ground();

	void Draw();
	int GetCurrentGroundY()const;
private:
	Segment _seg;
};

