#include "OnetimeSpawner.h"
#include "Enemy.h"
#include "Camera.h"

OnetimeSpawner::OnetimeSpawner(const Camera & cam, Position2f & pos, std::shared_ptr<Enemy> org):
	_camera(cam),_pos(pos),Spawner(org)
{
}

OnetimeSpawner::~OnetimeSpawner()
{
}

std::shared_ptr<Enemy> OnetimeSpawner::Spawn()
{
	auto ret = CreateClone();
	ret->SetPosition(_pos);
	return ret;
}

void OnetimeSpawner::Update(std::vector<std::shared_ptr<Actor>>& actors)
{
	if (_isSpawned) return;
	auto range = _camera.GetViewRange();
	if (range.Left() < _pos.x && _pos.x <range.Right())
	{
		actors.push_back(Spawn());
		_isSpawned = true;
	}
}
