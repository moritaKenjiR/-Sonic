#include "PauseScene.h"


PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Input & input)
{
	
}

void PauseScene::Draw()
{
	DrawString(100, 100, "pauseScene", 0xfffff);
}
