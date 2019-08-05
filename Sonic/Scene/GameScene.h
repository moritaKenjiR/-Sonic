#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>
class Actor;
class Player;
class Camera;
class Background;
class Stage;
class Ground;
class Block;
class Ant;
class Mantis;
class HUD;
class EventQueue;
class Event;
class Spawner;

class GameScene :
	public BaseScene
{
public:
	GameScene(SceneMng& mng);
	~GameScene();
	void Update(const Input& input)override final;
	void Draw()override final;
	std::shared_ptr<Ground> _ground;
	
	void CheckPlayerAndBlock(bool& isOn);
	void CheckPlayerAndActor();
	void CheckPlayerAndEvent();
private:
	std::shared_ptr<Player> _player;
	std::vector<std::shared_ptr<Actor>> _actors;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::vector<std::shared_ptr<Spawner>> _spawners;
	std::vector<std::shared_ptr<Event>> _events;
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<Stage> _stage;
	std::unique_ptr<Background> _bg;
	std::shared_ptr<HUD> _hud;
	std::shared_ptr<EventQueue> _eventQueue;

	int _BgmH;
};

