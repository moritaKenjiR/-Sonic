#include "SideEdgeSpawner.h"
#include "Enemy.h"
#include <DxLib.h>

constexpr int spawn_interval = 120;

SideEdgeSpawner::SideEdgeSpawner(const Camera & cam, Position2f & pos, std::shared_ptr<Enemy> org):
	_camera(cam), _pos(pos), Spawner(org)
{
}

SideEdgeSpawner::~SideEdgeSpawner()
{
}

std::shared_ptr<Enemy> SideEdgeSpawner::Spawn()
{
	auto ret = CreateClone();
	auto range = _camera.GetViewRange();

	auto spawnOffset = 0;
	if (_spawndir) spawnOffset = -_camera.GetViewRange().size.w;
	else spawnOffset = _camera.GetViewRange().size.w;

	ret->SetPosition(Position2f(range.center.x + spawnOffset, _pos.y));
	return ret;
}

void SideEdgeSpawner::Update(std::vector<std::shared_ptr<Actor>>& actors)
{
	auto range = _camera.GetViewRange();
	
	if (range.Left() < _pos.x && _pos.x < range.Right() && _frame <= 0)
	{
		actors.push_back(Spawn());
		if (_spawndir) _spawndir = false;
		else _spawndir = true;
		_frame = spawn_interval;
	}
	_frame--;
}

void SideEdgeSpawner::Draw()
{
	auto offset = _camera.GetOffset();
	DrawCircle(_pos.x - offset.x, _pos.y - offset.y, 50, 0x000000, false, 3);
}
