#include "BlockFactory.h"
#include "Geometry.h"
#include "Game/Camera.h"
#include "Collision.h"
#include <DxLib.h>
#include "Application.h"
#include "System/ImageLoader.h"

static constexpr int fix_width = 5;

Block::Block(Rect rect,const Camera& cam):_rect(rect),_camera(cam)
{
	ImageData data;
	Application::Instance().GetFileSystem()->Load("img/atlas0.png", data);
	_blockH = data.GetHandle();
}

const BoxCollider & Block::GetCollider() const
{
	BoxCollider bc(_rect);
	return bc;
}

BlockFactory::BlockFactory(const Camera& cam):_camera(cam)
{
	ImageData data;
	Application::Instance().GetFileSystem()->Load("img/atlas0.png", data);
	_blockH = data.GetHandle();
}


BlockFactory::~BlockFactory()
{
}

std::unique_ptr<Block> BlockFactory::Create(BlockType type, const Position2 pos)
{

	class Brick : public Block
	{
	public:
		Brick(const Position2& pos, const Camera& cam) : Block(Rect(pos, Size(48, 48)),cam)
		{
		}

		void Update()override
		{

		}

		void Draw()override
		{
			auto offset = _camera.GetOffset();
			DrawRectExtendGraph(_rect.Left() - offset.x, _rect.Top() - offset.y
				, _rect.Right() - offset.x, _rect.Bottom() - offset.y, 224, 128, 32, 32, _blockH, true);
		}

		void OnCollision(Actor* actor, const BoxCollider& col)override
		{

		}
	};


	class Slide : public Block
	{
		const int  _speed;
	public:
		Slide(const Position2& pos, const Camera& cam, unsigned int runLength = 1) :
			Block(Rect(pos, Size(48, 48)), cam), _speed((int)runLength)
		{

		};
		void Update()override
		{

		}

		void Draw()override
		{
			auto offset = _camera.GetOffset();
			DrawRectExtendGraph(_rect.Left() - offset.x, _rect.Top() - offset.y
				, _rect.Right() - offset.x, _rect.Bottom() - offset.y, 224, 128, 32, 32, _blockH, true);
		}

		void OnCollision(Actor* actor, const BoxCollider& col)override
		{

		}
	};


	class Pendulum : public Block
	{
	private:
		//static constexpr int fix_width = 5;
		Position2f _pos;
		Vector2f _vel;
		Position2f _pivot;
		float _g;
		bool _isVisible;
		int _frame = 0;
		int _length;
		void (Pendulum::*_updater)();
	public:
		Pendulum(const Position2& pos, const Camera& cam):
			Block(Rect(pos, Size(48, 48)), cam)
		{

		}
		void NormalUpdate()
		{
			auto tensionVec = _rect.center.ToFloatVec() - _pivot;
			float theta = atan2f(tensionVec.y, tensionVec.x);
			_vel.x = _g * cos(theta) * sin(theta);
			_vel.y = _g * cos(theta) * cos(theta);

			_pos += _vel;
			tensionVec = _pos - _pivot;
			_pos = _pivot + tensionVec.Normalized() *_length;

			_rect.center = _pos.ToIntVec();
		}
		void FragileUpdate()
		{

		}

		void Update()override
		{
			(this->*_updater)();
		}
		void Draw()override
		{

		}
	};


	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(pos,_camera);
	}
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(pos, _camera);
	}
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(pos, _camera);
	}
}

