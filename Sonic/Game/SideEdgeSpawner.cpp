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
	ret->SetPosition(_pos);
	return ret;
}

void SideEdgeSpawner::Update(std::vector<std::shared_ptr<Actor>>& actors)
{
	auto range = _camera.GetViewRange();
	if (range.Left() < _pos.x && _pos.x < range.Right() && _frame <= 0)
	{
		actors.push_back(Spawn());
		_frame = spawn_interval;
	}
	_frame--;
}

void SideEdgeSpawner::Draw()
{
	auto offset = _camera.GetOffset();
	DrawCircle(_pos.x - offset.x, _pos.y - offset.y, 50, 0x000000, false, 3);
}
