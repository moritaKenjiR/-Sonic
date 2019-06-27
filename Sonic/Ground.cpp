#include "Ground.h"
#include <DxLib.h>


Ground::Ground()
{
	_seg.posa = Position2f(0, 200);
	_seg.posb = Position2f(500, 100);
}


Ground::~Ground()
{
}

void Ground::Draw()
{
	DrawLine(0, 350, 5000, 350, 0xa03030);
	_seg.Draw();
}

int Ground::GetCurrentGroundY() const
{
	posb.y - posa.y / posb.x - posa.x
		return posa.y +grad *()
	return 350;
}
