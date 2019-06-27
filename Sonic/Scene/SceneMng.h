#pragma once
#include <memory>
#include <deque>
class BaseScene;
class Input;

class SceneMng
{
public:
	SceneMng();
	~SceneMng();

	void ChangeScene(std::unique_ptr<BaseScene> nextscene);
	void PushScene(std::unique_ptr<BaseScene> nextscene);
	void PopScene();
	void Update( Input& input);
private:
	std::deque<std::unique_ptr<BaseScene>> _scene;
};

