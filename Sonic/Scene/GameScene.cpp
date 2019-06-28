#include "GameScene.h"
#include "../Input/Input.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "../Game/Camera.h"
#include "../Game/Player.h"
#include "../Background.h"
#include "../Ground.h"


GameScene::GameScene(SceneMng & mng) : BaseScene(mng)
{
	_camera = std::make_unique<Camera>();
	_player = std::make_shared<Player>(*_camera);
	_actors.push_back(_player);
	_stage = std::make_unique<Stage>(*_camera);
	_bg = std::make_unique<Background>(*_camera);
	_ground = std::make_unique<Ground>(*_player,*_camera);
	_camera->AddPlayer(_player);
	_player->GetGroundP(_ground);

	_bg->AddParts("img/bg-clouds.png",Position2(-300,0),1.0f,true,Background::LayoutType::repeat,Size(160*5,208*5),-1);
	_bg->AddParts("img/bg-mountains.png", Position2(-300, 0), 1.5f, true, Background::LayoutType::repeat, Size(160*5, 208*5), -1);
	_bg->AddParts("img/bg-trees.png", Position2(-300,0), 2.0f, true, Background::LayoutType::repeat, Size(160*5, 208*5), -1);
	_stage->DataLoad("img/temp_bg.jpg");
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
	_camera->Update();

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
	_stage->Draw();
	_bg->DrawBg();
	_ground->Draw();
	for (auto actor : _actors)
	{
		actor->Draw();
	}
	DrawString(100, 100, "GameScene", 0xffffff);
}

