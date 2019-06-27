#include "PauseScene.h"
#include "../Input/Input.h"


PauseScene::PauseScene(SceneMng & mng) :BaseScene(mng)
{

}

PauseScene::~PauseScene()
{
}

void PauseScene::Update( Input & input)
{
	if (input.Ispressed(0, "pause") && !input.IsTriggered(0, "pause"))
	{
		_mng.PopScene();
	}
}

void PauseScene::Draw()
{
	DrawString(100, 125, "pauseScene", 0xfffff);
}
