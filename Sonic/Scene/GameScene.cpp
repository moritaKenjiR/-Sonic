#include "GameScene.h"
#include "../Input/Input.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "../Game/Player.h"


GameScene::GameScene(SceneMng & mng) : BaseScene(mng)
{
	_actors.push_back(std::make_shared<Player>());
}

GameScene::~GameScene()
{
}

void GameScene::Update(const Input & input)
{
	for (auto actor : _actors)
	{
		actor->Update(input);
	}

	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<ResultScene>(_mng));
	}
	if (input.Ispressed(0, "pause") && !input.IsTriggered(0, "pause"))
	{
		_mng.PushScene(std::make_unique<PauseScene>(_mng));
	}
}

void GameScene::Draw()
{
	DrawString(100, 100, "GameScene", 0xffffff);
	for (auto actor : _actors)
	{
		actor->Draw();
	}
}

