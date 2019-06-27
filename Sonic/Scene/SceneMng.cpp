#include "SceneMng.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "GameScene.h"


SceneMng::SceneMng() 
{
	_scene.push_front(std::make_unique<TitleScene>((*this)));
}


SceneMng::~SceneMng()
{
}

void SceneMng::ChangeScene(std::unique_ptr<BaseScene> nextscene)
{
	_scene.clear();
	_scene.push_front(move(nextscene));
}

void SceneMng::PushScene(std::unique_ptr<BaseScene> nextscene)
{
	_scene.push_front(move(nextscene));
}

void SceneMng::PopScene()
{
	_scene.pop_front();
}

void SceneMng::Update( Input & input)
{
	_scene.front()->Update(input);
	for (auto rit = _scene.rbegin(); rit != _scene.rend(); ++rit)
	{
		(*rit)->Draw();
	}
}
