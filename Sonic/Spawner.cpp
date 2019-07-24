#include "Spawner.h"

using namespace std;

Spawner::Spawner(std::shared_ptr<Enemy> org):_original(org)
{
}

Spawner::~Spawner()
{
}

std::shared_ptr<Enemy> Spawner::CreateClone()
{
	return std::shared_ptr<Enemy>();
}
