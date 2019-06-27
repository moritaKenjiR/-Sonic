#include "ResultScene.h"
#include "../Input/Input.h"
#include "TitleScene.h"


ResultScene::ResultScene(SceneMng & mng) :BaseScene(mng)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Input & input)
{
	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<TitleScene>(_mng));
	}
}

void ResultScene::Draw()
{
	DrawString(100, 100, "ResultScene", 0xffffff);
}
