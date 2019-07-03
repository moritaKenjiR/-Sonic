#include "Background.h"
#include<DxLib.h>
#include "Game/Camera.h"
#include "Application.h"
#include "Geometry.h"


Background::Background(const Camera & cam):_camera(cam)
{
}

Background::~Background()
{
}

void Background::Init()
{
}

void Background::AddParts(const char * filepath, const Position2 & pos, float rate, bool fromBottom, LayoutType type,Size size, int repeatX)
{
	auto wsize = Application::Instance().GetConfig().GetScreenSize();
	auto handle = LoadGraph(filepath);
	int w, h;
	GetGraphSize(handle, &w, &h);
	float scale = 1.0f;
	if (size.w > 0) {
		scale = static_cast<float>(size.w) / static_cast<float>(w);
		w = size.w;
	}
	if (size.h > 0) {
		h = size.h;
	}
	else {
		h *= scale;
	}

	if (repeatX == -1) {
		repeatX = w;
	}
	auto p = pos;
	if (fromBottom) {
		p.y = wsize.h - pos.y - h;
	}
	_bgparts.push_back(Obj(handle, p, rate, type, repeatX, Size(w,h)));
}

void Background::Update()
{
}

void Background::DrawBg()
{
	auto offset = _camera.GetOffset();
	for (auto& part : _bgparts) 
	{
		int w, h;
		GetGraphSize(part.handle, &w, &h);
		auto poffset = offset * part.rate;
		auto pos = part.initpos - Position2(poffset.x%(part.repeatX), poffset.y);

		DrawExtendGraph(
			pos.x,
			pos.y,
			pos.x + part.size.w,
			pos.y + part.size.h,
			part.handle,
			true);

		DrawExtendGraph(
			pos.x + part.repeatX,
			pos.y,
			pos.x + part.repeatX + part.size.w,
			pos.y + part.size.h,
			part.handle,
			true);

		DrawExtendGraph(
			pos.x + part.repeatX*2,
			pos.y,
			pos.x + part.repeatX*2 + part.size.w,
			pos.y + part.size.h,
			part.handle,
			true);
	}
}

