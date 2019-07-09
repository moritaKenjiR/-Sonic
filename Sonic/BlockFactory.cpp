#include "BlockFactory.h"
#include "Geometry.h"
#include "Game/Camera.h"
#include "Collision.h"
#include <DxLib.h>

Block::Block(Rect rect,const Camera& cam):_rect(rect),_camera(cam)
{
}

BlockFactory::BlockFactory(const Camera& cam):_camera(cam)
{
	_blockH = LoadGraph("img/atlas0.png", true);
}


BlockFactory::~BlockFactory()
{
}

std::unique_ptr<Block> BlockFactory::Create(BlockType type, const Position2 pos)
{
	class Brick : public Block
	{
	public:
		int _blockH;
		Brick(const Position2& pos) : Block(Rect(pos, Size(48, 48)),_camera)
		{
			_blockH = LoadGraph("img/atlas0.png", true);
		}

		void Update()override
		{

		}

		void Draw()override
		{
			auto offset = _camera.GetOffset();
			DrawRectExtendGraph(_rect.Left() - offset.x,_rect.Top() - offset.y
							,_rect.Right() - offset.x,_rect.Bottom() - offset.y,224,128,32,32,_blockH,true);
		}

		void OnCollision(Actor* actor, const BoxCollider& col)override
		{

		}
	};


	if (type == BlockType::brick)
	{
		std::unique_ptr<Block> ptr;
		ptr = std::make_unique<Brick>(pos);
		return ptr;
	}
}

