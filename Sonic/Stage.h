#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Geometry.h"
class Camera;
class Ground;
class Block;
class BlockFactory;
class Spawner;
class Player;
class Event;
class EventQueue;

enum class EnemyType {
	ant = 1,
	mantis = 2,
	lizard = 3,
	nightmare = 4,
	ant_side = 5,
	mantis_side = 6,
	lizard_random = 7
};

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

class Stage
{
private:
	const Camera& _camera;
	const Player& _player;
	EventQueue& _eventQueue;
	int _bgH;
	std::map<unsigned char, std::vector<Position2f>> _terraPositions;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::vector<std::shared_ptr<Spawner>> _spawners;
	std::vector<std::shared_ptr<Event>> _events;
public:
	Stage(const Camera& cam,const Player& pl, EventQueue& eventq);
	~Stage();

	void DataLoad(const char* path);
	void BuildGround(Ground& ground);
	void BuildBlockLayer(StageHeader &stgheader, int handle);
	void BuildSpawnerLayer(StageHeader &stgheader, int handle);
	void BuildEventLayer(StageHeader &stgheader, int handle);

	void Update();

	void Draw();

	std::vector<std::shared_ptr<Block>>& GetBlocks();
	std::vector<std::shared_ptr<Spawner>>& GetSpawners();
	std::vector<std::shared_ptr<Event>>& GetEvents();

};

