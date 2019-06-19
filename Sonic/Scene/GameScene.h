#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>
class Actor;

class GameScene :
	public BaseScene
{
public:
	GameScene(SceneMng& mng);
	~GameScene();
	void Update(const Input& input)override final;
	void Draw()override final;
private:
	std::vector<std::shared_ptr<Actor>> _actors;
};

