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
	void DrawBottomGround(const Position2f& posa, const Position2f& posb);
	int GetCurrentGroundY(float& grad)const;
	int GetCurrentDeadLine()const;
	void AddSegment(const Segment& seg);
	void AddSegment(const Position2f& posa, const Position2f& posb);
private:
	Player& _player;
	const Camera& _camera;
	std::vector<Segment> _segments;
	Segment _seg;
	int _handle;
};

