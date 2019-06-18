#include "GameScene.h"
#include "Input.h"
#include "ResultScene.h"


GameScene::GameScene(SceneMng & mng) : BaseScene(mng)
{
}

GameScene::~GameScene()
{
}

void GameScene::Update(const Input & input)
{
	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<ResultScene>(_mng));
	}
}

void GameScene::Draw()
{
	DrawString(100, 100, "TitleScene", 0xffffff);
}

