#include "Coin.h"
#include "../System/Loader.h"
#include "../System/ImageLoader.h"
#include "../Application.h"
#include "Camera.h"
#include "EventQueue.h"
#include <DxLib.h>
#include "ScoreUpper.h"
#include "Event.h"
#include "Actor.h"
#include "Player.h"

constexpr int coin_score = 100;

Coin::Coin(const Camera& cam, const Position2& pos, EventQueue& eventq) 
	:_bc(Rect(pos,Size(32,32))),_camera(cam),Event(eventq)
{
	ImageData data;
	Application::Instance().GetFileSystem()->Load("img/atlas.png", data);
	_imgH = data.GetHandle();
	_coinSE = LoadSoundMem("se/coin.wav");
}


Coin::~Coin()
{
}

EventType Coin::GetType() const
{
	return EventType::coin;
}

void Coin::Update()
{
}

void Coin::Draw()
{
	if (!_isAvailable) return;
	auto range = _camera.GetViewRange();
	if (range.Left() < _bc.GetRect().center.x  && _bc.GetRect().center.x < range.Right())
	{
		auto offset = _camera.GetOffset();
		DrawRectRotaGraph(_bc.GetRect().center.x - offset.x, _bc.GetRect().center.y - offset.y,
			16, 2, 10, 13, 5.0f, 0.0f, _imgH, true);
	}
}

 BoxCollider& Coin::GetCollider()
{
	return _bc;
}

void Coin::OnCollision(Actor * actor, const BoxCollider & col)
{
	_isAvailable = false;
	PlaySoundMem(_coinSE,DX_PLAYTYPE_BACK);
	_eventQueue.AddEvent(this);
	_eventQueue.AddEvent(new ScoreUpper(_eventQueue,coin_score));
}
