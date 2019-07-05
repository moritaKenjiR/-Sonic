#pragma once
#include <memory>
#include "Geometry.h"

enum class BlockType {
	non,
	brick,
	lift,
	slide,
	pendulum,
	broken,
};

class Actor;
class BlockCollider;
class Camera;

class Block
{
protected:
	Rect _rect;
	const Camera& _camera;
	Block( Rect rect,const Camera& cam);
	
public:
	virtual void Update() = 0;

	virtual void Draw() = 0;


	virtual void OnCollision(Actor* actor, const BlockCollider& col) = 0;

	const BlockCollider& GetCollider()const;
};


class BlockFactory 
{
public:
	BlockFactory(const Camera& cam);
	~BlockFactory();
	int _blockH;
	std::unique_ptr<Block> Create(BlockType type, const Position2 pos);
private:
	const Camera& _camera;
};

