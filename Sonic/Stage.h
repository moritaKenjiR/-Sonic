#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Geometry.h"
class Camera;
class Ground;
class Block;
class BlockFactory;

class Stage
{
private:
	const Camera& _camera;
	int _bgH;
	std::map<unsigned char, std::vector<Position2f>> _terraPositions;
	std::vector<std::unique_ptr<Block>> _blocks;
public:
	Stage(const Camera& cam);
	~Stage();

	void DataLoad(const char* path);
	void BuildGround(Ground& ground);

	void Update();

	void Draw();
	std::vector<std::unique_ptr<Block>> Blocks();
};
