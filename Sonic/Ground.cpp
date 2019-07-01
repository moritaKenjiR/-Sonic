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
		auto bx = (i + 1) * 100;
		auto ay = 300 - 200 * sin(DX_PI*(float)i / 8.0f);
		auto by = 300 - 200 * sin(DX_PI*(float)(i+1) / 8.0f);
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
		int count = (int)(seg.posb.x - seg.posa.x) / 64;
		int mod = (int)(seg.posb.x - seg.posa.x)% 64;
		float grad = (seg.posb.y - seg.posa.y) /(seg.posb.x - seg.posa.x);

		DrawLine(seg.posa.x - offset.x, seg.posa.y - offset.y, seg.posb.x - offset.x, seg.posb.y - offset.y, 0xff0000, true);
		for (int i = 0; i < count; ++i)
		{
			Position2f posa(seg.posa.x + i * 64 - offset.x,seg.posa.y + grad * i * 64 - offset.y);
			Position2f posb(seg.posa.x + (i + 1) * 64 - offset.x,seg.posa.y + grad * (i + 1) * 64 - offset.y);
			DrawBottomGround(posa,posb);
		}

		Position2f posa(seg.posa.x + count * 64 - offset.x, seg.posa.y + grad * count * 64 -
			offset.y);
		Position2f posb(seg.posa.x + count * 64 + mod - offset.x, seg.posa.y + grad *
			(count * 64 + mod) - offset.y);
		DrawBottomGround(posa, posb);
	}
}

void Ground::DrawBottomGround(const Position2f & posa, const Position2f & posb)
{
	int width = posb.x - posa.x;
	width = min(width,64);

	//�\�w
	DrawRectModiGraphF(
		posa.x, posa.y,
		posb.x, posb.y,
		posb.x, posb.y + 64,
		posa.x, posa.y + 64,
		64, 32, 32, 32, _handle, true);

	float yposmax = max(posa.y, posb.y);
	//���w
	DrawRectModiGraphF(
		posa.x ,posa.y + 64,
		posb.x, posb.y + 64,
		posb.x, yposmax + 64 + 64,
		posa.x, yposmax + 64 + 64,
		64, 64, 32, 32, _handle, true);

	yposmax += 128;
	//�ȍ~�w
	while (yposmax < 640)
	{
		DrawRectExtendGraphF(
			posa.x , yposmax - 1,
			posb.x , yposmax + 64,
			64, 64, 32, 32, _handle, true);
		yposmax += 64;
	}
}

int Ground::GetCurrentGroundY(float& grad) const
{
	auto pos = _player.GetPosition();

	auto lambda = [pos](const Segment& s)
	{
		return s.posa.x <= pos.x && pos.x <= s.posb.x;
	};
	auto it = std::find_if(_segments.begin(), _segments.end(), lambda);
	if (it == _segments.end()) return INT_MIN;
	
	auto y = it->posa.y + grad * (pos.x - it->posa.x);
	do {
		grad = it->posb.y - it->posa.y / it->posb.x - it->posa.x;
		y = it->posa.y + grad * (pos.x - it->posa.x);
		it = find_if(it, _segments.end(), lambda);

		if (y >= pos.y - 100) break;

		it = find_if(it + 1, _segments.end(), lambda);
	} while (it != _segments.end());
	if (it == _segments.end()) return INT_MIN;

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
	return 1000;
}
