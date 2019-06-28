#pragma once
#include "Geometry.h"
#include <vector>
class Player;
class Camera;

class Ground
{
public:
	Ground(Player& pl,const Camera& cam);
	~Ground();

	void Draw();
	int GetCurrentGroundY(float& grad)const;
	int GetCurrentDeadLine()const;
private:
	Player& _player;
	const Camera& _camera;
	std::vector<Segment> _segments;
	Segment _seg;
	int _handle;
};

