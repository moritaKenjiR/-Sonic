#include "TitleScene.h"
#include "../Input/Input.h"
#include "GameScene.h"
#include "SceneMng.h"
#include "../Application.h"

constexpr int fade_interval = 60;

TitleScene::TitleScene(SceneMng& mng) :BaseScene(mng)
{
	_fadeCounter = 60;
	_titleBackH = LoadGraph("Image/title.png", true);
	_updater = &TitleScene::FadeinUpdate;
	_drawer = &TitleScene::FadeDrawer;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Input & input)
{
	(this->*_updater)(input);
}

void TitleScene::Draw()
{
	(this->*_drawer)();
}

void TitleScene::FadeinUpdate(const Input &)
{
	if (--_fadeCounter <= 0)
	{
		_updater = &TitleScene::WaitUpdate;
		_drawer = &TitleScene::NormalDrawer;
	}
}

void TitleScene::WaitUpdate(const Input & input)
{
	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{
		_updater = &TitleScene::FadeoutUpdate;
		_drawer = &TitleScene::FadeDrawer;
	}
}

void TitleScene::FadeoutUpdate(const Input &)
{
	if (++_fadeCounter >= fade_interval)
	{
		_mng.ChangeScene(std::make_unique<GameScene>(_mng));
	}
}

void TitleScene::FadeDrawer()
{
	auto wsize = Application::Instance().GetConfig().GetScreenSize();
	DrawGraph(256, 100, _titleBackH, true);
	DrawString(100, 100, "TitleScene", 0xffffff);

	auto blendval = _fadeCounter * 255 / fade_interval;
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendval);
	DrawBox(0, 0,wsize.x,wsize.y,0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDrawer()
{
	DrawGraph(256, 100, _titleBackH, true);
	DrawString(100, 100, "TitleScene", 0xffffff);
}
