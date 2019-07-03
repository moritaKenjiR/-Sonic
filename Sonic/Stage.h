#pragma once
#include <vector>
#include <map>
#include "Geometry.h"
class Camera;
class Ground;

class Stage
{
private:
	const Camera& _camera;
	int _bgH;
	std::map<unsigned char, std::vector<Position2f>> _terraPositions;
public:
	Stage(const Camera& cam);
	~Stage();

	void DataLoad(const char* path);
	void BuildGround(Ground& ground);

	void Update();

	void Draw();
};

