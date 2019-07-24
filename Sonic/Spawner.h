#pragma once
#include <memory>
#include "Geometry.h"
class Enemy;

class Spawner
{
public:
	Spawner(std::shared_ptr<Enemy> org);
	virtual ~Spawner();
	virtual std::shared_ptr<Enemy> Spawn() = 0;
	virtual void Update(std::vector<std::shared_ptr<Actor>>& actors) = 0;
protected:
	std::shared_ptr<Enemy> _original;
	std::shared_ptr<Enemy> CreateClone();
};

