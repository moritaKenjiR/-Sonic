#pragma once
#include "Spawner.h"
#include "../Geometry.h"

class Camera;

class PortalSpawner :
	public Spawner
{
public:
	PortalSpawner(const Camera& cam, Position2f& pos, std::shared_ptr<Enemy> org);
	~PortalSpawner();
	std::shared_ptr<Enemy> Spawn();
	void Update(std::vector<std::shared_ptr<Actor>>& actors)override final;
	void Draw();
private:
	const Camera& _camera;
	Position2f _pos;
	unsigned int _frame;
};

