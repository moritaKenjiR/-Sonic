#include "GameScene.h"
#include "../Input/Input.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "../Game/Camera.h"
#include "../Game/Player.h"
#include "../Background.h"
#include "../Ground.h"
#include "../Stage.h"
#include "../BlockFactory.h"
#include "../Collision.h"
#include "../Game/Enemy.h"
#include "../Game/Ant.h"
#include "../Game/OnetimeSpawner.h"
#include "../Game/Spawner.h"
#include "../Game/HUD.h"
#include "../Game/Event.h"


GameScene::GameScene(SceneMng & mng) : BaseScene(mng)
{
	_camera = std::make_unique<Camera>();
	_player = std::make_shared<Player>(*_camera);
	_actors.push_back(_player);
	_stage = std::make_unique<Stage>(*_camera,*_player);
	_stage->DataLoad("map/level1.fmf");
	_bg = std::make_unique<Background>(*_camera);
	_ground = std::make_unique<Ground>(*_player,*_camera);
	_hud = std::make_shared<HUD>();
	_stage->BuildGround(*_ground);
	_camera->AddPlayer(_player);
	_player->GetGroundP(_ground);

	auto antOrg = std::make_shared<Ant>(*_camera, *_player, 300, 300);
	_actors.push_back(antOrg);
	auto mantisOrg = std::make_shared<Ant>(*_camera, *_player, 1000, 200);
	_actors.push_back(mantisOrg);

	auto spawner = std::make_shared<OnetimeSpawner>(*_camera, Position2f(300, 300), antOrg);
	_actors.push_back(spawner->Spawn());

	_bg->AddParts("img/bg-clouds.png",Position2(-300,0),1.0f,true,Background::LayoutType::repeat,Size(160*5,208*5),-1);
	_bg->AddParts("img/bg-mountains.png", Position2(-300, 0), 1.5f, true, Background::LayoutType::repeat, Size(160*5, 208*5), -1);
	_bg->AddParts("img/bg-trees.png", Position2(-300,0), 2.0f, true, Background::LayoutType::repeat, Size(160*5, 208*5), -1);
	
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

	auto viewrange = _camera->GetViewRange();
	//ブロックとの当たり判定 
	_blocks = _stage->GetBlocks();
	for (auto& b : _blocks) {
		auto& brect = b->GetCollider().GetRect();
		//画面外は省く 
		if (brect.Right() < viewrange.Left() || brect.Left() > viewrange.Right()) {
			continue;
		}
		if (Collider::IsCollided(_player->GetCollider(), b->GetCollider())) {
			_player->OnDead();
			_camera->RemovePlayer(_player);
		}
	}
}

void GameScene::Draw()
{
	
	_bg->DrawBg();
	_ground->Draw();
	_stage->Draw();
	for (auto actor : _actors)
	{
		actor->Draw();
	}
	DrawString(100, 100, "GameScene", 0xffffff);


	for (auto block : _blocks)
	{
		block->Draw();
	}
	for (auto event : _events)
	{
		event->Draw();
	}

}

void GameScene::CheckPlayerAndBlock(bool& isOn)
{
}

void GameScene::CheckPlayerAndActor()
{
}

void GameScene::CheckPlayerAndEvent()
{
	if (_player->IsDie())return;

}

