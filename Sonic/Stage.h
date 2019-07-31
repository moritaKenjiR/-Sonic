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

