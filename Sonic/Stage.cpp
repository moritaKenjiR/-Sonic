#include "Stage.h"
#include <DxLib.h>
#include <algorithm>
#include "Ground.h"
#include "BlockFactory.h"
#include "Geometry.h"
#include "Collision.h"
constexpr int  block_size = 32;

Stage::Stage(const Camera & cam) :_camera(cam)
{
}

Stage::~Stage()
{
}

void Stage::DataLoad(const char * path)
{
	//�ð���ް���ͯ�ް�\����
	struct StageHeader {
		unsigned char identifier[4];		//̧�َ��ʎq
		unsigned int size;					//ͯ�ނ��������ް�����
		unsigned int mapWidth;			//ϯ�߂̉���
		unsigned int mapHeight;			//ϯ�߂̏c��
		unsigned char chipWidth;		//���߂̉���
		unsigned char chipHeight;		//���߂̏c��
		unsigned char layerCount;		//ڲ԰��
		unsigned char bitCount;			//�ް����ޯĶ���(8or16)
	};

	BlockFactory bf(_camera);

	auto handle = FileRead_open(path);
	StageHeader header = {};
	FileRead_read(&header, sizeof(header), handle);

	std::vector<unsigned char> terrawdata(header.mapHeight*header.mapWidth);
	FileRead_read(terrawdata.data(), terrawdata.size(), handle);

	std::vector<unsigned char> blockdata(header.mapHeight*header.mapWidth);
	FileRead_read(&blockdata,blockdata.size(), handle);

	FileRead_close(handle);


	for (size_t i = 0; i < terrawdata.size(); ++i)
	{
		auto no = terrawdata[i];
		if (no > 0)
		{
			_terraPositions[no - 1].emplace_back((i%header.mapWidth)*block_size,
																			(i / header.mapWidth)*block_size);
		}
	}
	//X�ſ��
	for (auto& vect : _terraPositions) {
		std::sort(vect.second.begin(), vect.second.end(),
						[](const Position2f& lpos, const Position2f& rpos) {
			return lpos.x < rpos.x;
		});
	}
	
	for (int y = 0; y < header.mapHeight; ++y)
	{
		for (int x = 0; x < header.mapWidth; ++x)
		{
			if (blockdata[(y*header.mapWidth) + x] == 1)
			{
				Position2 pos = { x*block_size,y*block_size };
				_blocks.push_back(bf.Create(BlockType::brick, pos));
			}
		}
	}
}

void Stage::BuildGround(Ground & ground)
{
	for (auto& terra : _terraPositions)
	{
		auto it = terra.second.begin();
		for (; it + 1 != terra.second.end(); ++it)
		{
			ground.AddSegment(*it, *(it + 1));
		}
		terra.second.clear();
	}
	_terraPositions.clear();
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (auto& block : _blocks)
	{
		block->Draw();
	}
}

std::vector<std::unique_ptr<Block>> Stage::Blocks()
{
	return _blocks;
}


class Pendulum : public Block
{
private:
	static constexpr int fix_width = 5;
	Position2f _pos;
	Vector2f _vel;
	Position2f _pivot;
	float _g;
	bool _isVisible;
	int _frame = 0;
	int _length;
	void (Pendulum::*_updater)();
public:
	void NormalUpdate()
	{
	
		auto tensionVec = _rect.center.ToFloatVec() - _pivot;
		float theta = atan2f(tensionVec.y, tensionVec.x);
		_vel.x = _g * cos(theta) * sin(theta);
		_vel.y = _g * cos(theta) * cos(theta);

		_pos += _vel;
		tensionVec = _pos - _pivot;
		_pos = _pivot + tensionVec.Normalize()*_length;

		_rect.center = _pos.ToIntVec();
	}
	void FragileUpdate()
	{

	}

	void Update()override
	{
		(_updater)
	}
	void Draw()override
	{

	}
};