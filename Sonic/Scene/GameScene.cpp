#include "GameScene.h"
#include "../Input/Input.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "../Game/Actor.h"
#include "../Game/Camera.h"
#include "../Game/Player.h"
#include "../Background.h"
#include "../Ground.h"
#include "../Stage.h"
#include "../BlockFactory.h"
#include "../Collision.h"
#include "../Game/Enemy.h"
#include "../Game/Ant.h"
#include "../Game/Mantis.h"
#include "../Game/OnetimeSpawner.h"
#include "../Game/Spawner.h"
#include "../Game/HUD.h"
#include "../Game/Event.h"
#include "../Game/EventQueue.h"
#include "Playing3DScene.h"

GameScene::GameScene(SceneMng & mng) : BaseScene(mng)
{
	_camera = std::make_unique<Camera>();
	_player = std::make_shared<Player>(*_camera);
	_actors.push_back(_player);
	_eventQueue = std::make_shared<EventQueue>();
	
	_bg = std::make_unique<Background>(*_camera);
	_ground = std::make_unique<Ground>(*_player,*_camera);
	_hud = std::make_shared<HUD>();
	_camera->AddPlayer(_player);
	_player->GetGroundP(_ground);

	_stage = std::make_unique<Stage>(*_camera, *_player,*_ground, *_eventQueue);
	_stage->DataLoad("map/level1.fmf");
	_stage->BuildGround(*_ground);
/*
	auto a = std::make_shared<Mantis>(*_camera, *_player, *_ground, *_eventQueue, 100, 100);
	a->_isAvailable = true;
	_actors.push_back(std::make_shared<Mantis>(*_camera,*_player, *_ground, *_eventQueue, 100, 100));*/

	_bg->AddParts("img/bg-clouds.png",Position2(-300,0),0.5f,true,Background::LayoutType::repeat,Size(160*4,208*4),-1);
	_bg->AddParts("img/bg-mountains.png", Position2(-300, 0), 0.7f, true, Background::LayoutType::repeat, Size(160*4, 208*4), -1);
	_bg->AddParts("img/bg-trees.png", Position2(-300,0), 1.0f, true, Background::LayoutType::repeat, Size(160*4, 208*4), -1);
	
	_BgmH = LoadSoundMem("bgm/bgm.wav");
	PlaySoundMem(_BgmH, DX_PLAYTYPE_LOOP);
}

GameScene::~GameScene()
{
}

void GameScene::Update(const Input & input)
{
	
	_spawners = _stage->GetSpawners();
	_blocks = _stage->GetBlocks();
	_events = _stage->GetEvents();

	for (auto actor : _actors)
	{
		actor->Update(input);
	}
	for (auto spawner : _spawners)
	{
		spawner->Update(_actors);
	}
	_camera->Update();
	_hud->Update();

	auto viewrange = _camera->GetViewRange();
	CheckPlayerAndActor();
	//CheckPlayerAndBlock();
	CheckPlayerAndEvent();
	//ブロックとの当たり判定 
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

	if (input.Ispressed(0, "ok") && !input.IsTriggered(0, "ok"))
	{
		_mng.ChangeScene(std::make_unique<Playing3DScene>(_mng));
	}
	if (input.Ispressed(0, "pause") && !input.IsTriggered(0, "pause"))
	{
		_mng.PushScene(std::make_unique<PauseScene>(_mng));
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
	_hud->Draw();
}

void GameScene::CheckPlayerAndBlock(bool& isOn)
{
	if (_player->IsDie())return;
	auto viewrange = _camera->GetViewRange();
}

void GameScene::CheckPlayerAndActor()
{
	if (_player->IsDie())return;
	auto viewrange = _camera->GetViewRange();
}

void GameScene::CheckPlayerAndEvent()
{
	auto viewrange = _camera->GetViewRange();
	if (_player->IsDie())return;
	for (auto & e : _events)
	{
		if (!e->IsAvailable()) continue;
		auto& brect = e->GetCollider().GetRect();
		if (brect.Right() < viewrange.Left() || brect.Left() > viewrange.Right())
		{
			continue;
		}
		if (Collider::IsCollided(_player->GetCollider(), e->GetCollider()))
		{
			e->OnCollision(&(*_player), _player->GetCollider());
		}
	}
}

