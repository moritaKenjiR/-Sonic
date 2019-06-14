#pragma once
#include <memory>
#include <stack>
class BaseScene;
class Input;

class SceneMng
{
public:
	SceneMng();
	~SceneMng();

	void ChangeScene(BaseScene* nextscene);
	void StackScene(BaseScene* nextscene);
	void Update(Input& input);
private:
	std::stack<std::shared_ptr<BaseScene>> _scene;
};

