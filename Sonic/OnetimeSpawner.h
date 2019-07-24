#pragma once
#include "Spawner.h"

class Camera;

class OnetimeSpawner :
	public Spawner
{
public:
	OnetimeSpawner(const Camera& cam,Position2f& pos, std::shared_ptr<Enemy> org);
	~OnetimeSpawner();
	std::shared_ptr<Enemy> Spawn();
	void Update(std::vector<std::shared_ptr<Actor>>& actors)override final;
private:
	const Camera& _camera;
	Position2f _pos;
	bool _isSpawned = false;
};

