#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>
class Actor;
class Player;
class Camera;
class Background;
class Stage;

class GameScene :
	public BaseScene
{
public:
	GameScene(SceneMng& mng);
	~GameScene();
	void Update(const Input& input)override final;
	void Draw()override final;
private:
	std::shared_ptr<Player> _player;
	std::vector<std::shared_ptr<Actor>> _actors;
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<Stage> _stage;
	std::unique_ptr<Background> _bg;
};

