#include "PauseScene.h"
#include "Input.h"


PauseScene::PauseScene(SceneMng & mng) :BaseScene(mng)
{

}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Input & input)
{
	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{
	}
}

void PauseScene::Draw()
{
	DrawString(100, 100, "pauseScene", 0xfffff);
}
