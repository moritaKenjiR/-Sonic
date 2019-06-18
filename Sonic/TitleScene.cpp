#include "TitleScene.h"
#include "Input.h"
#include "GameScene.h"
#include "SceneMng.h"


TitleScene::TitleScene(SceneMng& mng) :BaseScene(mng)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Input & input)
{
	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{

		_mng.ChangeScene(std::make_unique<GameScene>(_mng));
	}
}

void TitleScene::Draw()
{
	DrawString(100, 100, "TitleScene", 0xffffff);
}
