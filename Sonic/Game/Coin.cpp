#include "Coin.h"
#include "../System/Loader.h"
#include "../System/ImageLoader.h"
#include "../Application.h"
#include "Camera.h"
#include <DxLib.h>


Coin::Coin(const Camera& cam, const Position2& pos) :_bc(Rect(pos,Size(32,32))),_camera(cam)
{
	ImageData data;
	Application::Instance().GetFileSystem().Load("img/atlas.jpg", data);
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
	DrawRectRotaGraph(_bc.GetRect().center.x, _bc.GetRect().center.y,
														16, 2, 10, 13, 5.0f, 0.0f, _imgH, true);

}

const BoxCollider& Coin::GetCollider()
{
	return _bc;
}

void Coin::OnCollision(Actor & actor, const BoxCollider & col)
{
	_isAvailable = false;
	PlaySoundMem(_coinSE,DX_PLAYTYPE_BACK);
}
