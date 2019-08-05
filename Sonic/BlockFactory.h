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
class BoxCollider;
class Camera;

class Block
{
protected:
	Rect _rect;
	const Camera& _camera;
	Block( Rect rect,const Camera& cam);
	std::unique_ptr<BoxCollider> _collider;
	int _blockH;
	
public:
	virtual void Update() = 0;

	virtual void Draw() = 0;


	virtual void OnCollision(Actor* actor, const BoxCollider& col) = 0;

	BoxCollider& GetCollider();
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


