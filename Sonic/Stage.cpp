#include "Stage.h"
#include <DxLib.h>
#include <algorithm>
#include "Ground.h"
#include "BlockFactory.h"

constexpr int  block_size = 32;

Stage::Stage(const Camera & cam) :_camera(cam)
{
}

Stage::~Stage()
{
}

void Stage::DataLoad(const char * path)
{
	//½Ã°¼ŞÃŞ°À‚ÌÍ¯ÀŞ°\‘¢‘Ì
	struct StageHeader {
		unsigned char identifier[4];		//Ì§²Ù¯•Êq
		unsigned int size;					//Í¯ÀŞ‚ğœ‚¢‚½ÃŞ°À»²½Ş
		unsigned int mapWidth;			//Ï¯Ìß‚Ì‰¡•
		unsigned int mapHeight;			//Ï¯Ìß‚Ìc•
		unsigned char chipWidth;		//Á¯Ìß‚Ì‰¡•
		unsigned char chipHeight;		//Á¯Ìß‚Ìc•
		unsigned char layerCount;		//Ú²Ô°”
		unsigned char bitCount;			//ÃŞ°À‚ÌËŞ¯Ä¶³İÄ(8or16)
	};

	BlockFactory _bf(_camera);

	auto handle = FileRead_open(path);
	StageHeader header = {};
	FileRead_read(&header, sizeof(header), handle);

	std::vector<unsigned char> terrawdata(header.mapHeight*header.mapWidth);


	FileRead_read(terrawdata.data(), terrawdata.size(), handle);
	unsigned char tmp;
	for (int y = 0; y < header.mapHeight; ++y)
	{
		for (int x = 0; x < header.mapWidth; ++x)
		{
			FileRead_read(&tmp, sizeof(tmp), handle);
			if (tmp == 1)
			{
				_blocks.push_back(_bf.Create((BlockType)tmp,Position2(x*block_size,y*block_size)));
			}
		}
	}

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
	//X‚Å¿°Ä
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
