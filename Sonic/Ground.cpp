#include "Ground.h"
#include <DxLib.h>
#include <algorithm>
#include "Game/Player.h"
#include "Game/Camera.h"

Ground::Ground(Player& pl, const Camera& cam):_player(pl),_camera(cam)
{
	_seg.posa = Position2f(0, 200);
	_seg.posb = Position2f(500, 100);

	for (int i = 0; i < 800; ++i)
	{
		auto ax = i * 100;
		auto bx = (i - 1) * 100;
		auto ay = 300 - 200 * sin(DX_PI*(float)i / 8.0f);
		auto by = 300 - 200 * sin(DX_PI*(float)(i-1) / 8.0f);
		_segments.emplace_back(ax, ay, bx, by);
	}
	_handle = LoadGraph("img/atlas0.png", true);
}


Ground::~Ground()
{
}

void Ground::Draw()
{
	DrawRectModiGraphF(
		0, 0,
		128, 128,
		128, 256,
		0, 128,
		64,
		32,
		32,
		32,
		_handle,true);

	auto offset = _camera.GetOffset();
	DrawLine(0+ offset.x, 500+offset.y, 5000+offset.x, 500 + offset.y, 0xa03030);
	for (auto& seg : _segments)
	{
		int count = (int)(seg.posb.x - seg.posa.x+63) / 64;
		int mod = (int)(seg.posb.x - seg.posa.x + 63)% 64;
		float grad = seg.posb.y - seg.posa.y /seg.posb.x - seg.posa.x;

		DrawLine(seg.posa.x - offset.x, seg.posa.y - offset.y, seg.posb.x - offset.x, seg.posb.y - offset.y, 0xff0000, true);
		for (int i = 0; i < count; ++i)
		{
			Position2 posa(seg.posa.x + i * 64 - offset.x, seg.posa.y + grad * i * 64 - offset.y);
			Position2 posb(seg.posb.x + (i + 1) * 64 - offset.x, seg.posb.y + grad * (i + 1) * 64 - offset.);
			DrawRectModiGraphF(
				posa.x,posa.y,
				posb.x,posb.y,
				posb.x,posb.y+ 64,
				posa.x,posa.y,
				64,32,32,32,_handle, true);
		}
		float yposmax = max(seg.posa.y - offset.y, seg.posb.y - offset.y);
		DrawRectModiGraphF(
			seg.posa.x - offset.x, seg.posa.y - offset.y + 64,
			seg.posb.x - offset.x, seg.posb.y - offset.y + 64,
			seg.posb.x - offset.x, yposmax + 64 + 64,
			seg.posa.x - offset.x, yposmax + 64 + 64,
			64,64,32,32,_handle, true);

		yposmax += 64;
		while (yposmax < 640)
		{
			DrawRectExtendGraphF(
				seg.posa.x - offset.x, yposmax,
				seg.posb.x - offset.x, yposmax + 64,
				64, 64, 32, 32, _handle, true);
			yposmax += 64;
		}
	}
}

int Ground::GetCurrentGroundY(float& grad) const
{
	auto pos = _player.GetPosition();
	auto it = std::find_if(_segments.begin(), _segments.end(), [pos](const Segment& s)
	{
		return s.posa.x <= pos.x && pos.x <= s.posb.x;
	});
	if (it == _segments.end()) return INT_MIN;
	
	grad = it->posb.y - it->posa.y / it->posb.x - it->posa.x;
	auto y = it->posa.y + grad * (pos.x - it->posa.x);
	if (fabsf(pos.x - it->posa.x) < 4.0f)
	{
		if (it == _segments.begin()) return y;
		float t = fabsf(pos.x - it->posa.x) / 4.0f;
		auto& prv = *(it - 1);
		auto grad2 = (prv.posb.y - prv.posa.y) / (prv.posb.x - prv.posa.x);
		grad = grad * t + (1.0f - t)*(grad2 + grad) / 2;
	}
	else if (fabsf(pos.x - it->posb.x) < 4.0f) 
	{
		if (it + 1 == _segments.end())return y;
		float t = fabsf(pos.x - it->posb.x) / 4.0f;
		auto& next = *(it + 1);
		auto grad2 = (next.posb.y - next.posa.y) / (next.posb.x - next.posa.x);
		grad = grad * t + (1.0f - t)*(grad2 + grad) / 2;
	}
	return y;
}

int Ground::GetCurrentDeadLine() const
{
	return 0;
}
