#include "HUD.h"
#include "../System/Loader.h"
#include "../System/ImageLoader.h"
#include "../Application.h"
#include <DxLib.h>
#include "Event.h"


HUD::HUD()
{
}


HUD::~HUD()
{
	ImageData data;
	Application::Instance().GetFileSystem().Load("img/atlas.jpg", data);
	_coinH = data.GetHandle();
}

void HUD::Update()
{
}

void HUD::Draw()
{
	DrawRectRotaGraph(50,50,
		16, 2, 10, 13, 3.0f, 0.0f, _coinH, true);
	DrawFormatString(70, 45, 0xffffff, "~%d", _coinNum);

	DrawFormatString(150, 45, 0xffffff, "~%d", _score);
}

bool HUD::OnNotify(const Event* e)
{
	if (e->GetType() == EventType::coin)
	{
		_coinNum++;
		return true;
	}
	if (e->GetType() == EventType::score)
	{
		_score += e->GetValue();
		return true;
	}
	return false;
}
