#include "Stage.h"
#include <DxLib.h>
#include <algorithm>
#include "Ground.h"
#include "Game/Player.h"
#include "Game/Event.h"
#include "Game/EventQueue.h"
#include "BlockFactory.h"
#include "Geometry.h"
#include "Collision.h"
#include "Game/Camera.h"
#include "Game/Spawner.h"
#include "Game/OnetimeSpawner.h"
#include "Game/SideEdgeSpawner.h"
#include "Game/Ant.h"
#include "Game/Mantis.h"
constexpr int  block_size = 32;

Stage::Stage(const Camera & cam, const Player& pl, Ground& ground, EventQueue& eventq) :_camera(cam),_player(pl),_ground(ground),_eventQueue(eventq)
{
}

Stage::~Stage()
{
}

void Stage::DataLoad(const char * path)
{
	

	

	auto handle = FileRead_open(path);
	StageHeader header = {};
	FileRead_read(&header, sizeof(header), handle);

	std::vector<unsigned char> terrawdata(header.mapHeight*header.mapWidth);
	FileRead_read(terrawdata.data(), terrawdata.size(), handle);

	if (header.layerCount >= 2);
	//BuildBlockLayer(header,handle);
	//BuildSpawnerLayer(header, handle);
	//BuildEventLayer(header, handle);

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
	//XÇ≈ø∞ƒ
	for (auto& vect : _terraPositions) {
		std::sort(vect.second.begin(), vect.second.end(),
						[](const Position2f& lpos, const Position2f& rpos) {
			return lpos.x < rpos.x;
		});
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

void Stage::BuildBlockLayer(StageHeader & stgheader, int handle)
{
	BlockFactory bf(_camera);
	std::vector<unsigned char> blockdata(stgheader.mapHeight*stgheader.mapWidth);
	FileRead_read(blockdata.data(), blockdata.size(), handle);

	for (int y = 0; y < stgheader.mapHeight; ++y)
	{
		for (int x = 0; x < stgheader.mapWidth; ++x)
		{
			if (blockdata[(y*stgheader.mapWidth) + x] == 1)
			{
				Position2 pos = { x*block_size,y*block_size };
				_blocks.push_back(bf.Create(BlockType::brick, pos));
			}
		}
	}
}

void Stage::BuildSpawnerLayer(StageHeader & stgheader, int handle)
{
	std::vector<unsigned char> spawnerdata(stgheader.mapHeight*stgheader.mapWidth);
	FileRead_read(spawnerdata.data(), spawnerdata.size(), handle);
	//Ãﬂ€ƒ¿≤ÃﬂçÏê¨
	auto ant = std::make_shared<Ant>(_camera, _player,_ground,_eventQueue,0, 0);
	auto mantis = std::make_shared<Mantis>(_camera, _player, _ground, _eventQueue, 0, 0);

	for (int y = 0; y < stgheader.mapHeight; ++y)
	{
		for (int x = 0; x < stgheader.mapWidth; ++x)
		{
			Position2f pos = { (float)(x*block_size),(float)(y*block_size) };
			switch (spawnerdata[(y*stgheader.mapWidth) + x])
			{
			case 1:
				_spawners.push_back(std::make_shared<OnetimeSpawner>(_camera,pos,ant));
				break;
			case 2:
				_spawners.push_back(std::make_shared<OnetimeSpawner>(_camera, pos, mantis));
				break;
			case 5:
				_spawners.push_back(std::make_shared<SideEdgeSpawner>(_camera, pos, ant));
				break;
			case 6:
				_spawners.push_back(std::make_shared<SideEdgeSpawner>(_camera, pos, mantis));
			}
		}
	}
}

void Stage::BuildEventLayer(StageHeader & stgheader, int handle)
{

	std::vector<unsigned char> eventdata(stgheader.mapHeight*stgheader.mapWidth);
	FileRead_read(eventdata.data(), eventdata.size(), handle);

	for (int y = 0; y < stgheader.mapHeight; ++y)
	{
		for (int x = 0; x < stgheader.mapWidth; ++x)
		{
			Position2f pos = { (float)(x*block_size),(float)(y*block_size) };
			switch (eventdata[(y*stgheader.mapWidth) + x])
			{
			case 1:
				break;
			case 2:
				break;
			case 5:
				break;
			case 6:
				break;
			}
		}
	}
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

std::vector<std::shared_ptr<Block>>& Stage::GetBlocks()
{
	return _blocks;
}

std::vector<std::shared_ptr<Spawner>>& Stage::GetSpawners()
{
	return _spawners;
}

std::vector<std::shared_ptr<Event>>& Stage::GetEvents()
{
	return _events;
}
