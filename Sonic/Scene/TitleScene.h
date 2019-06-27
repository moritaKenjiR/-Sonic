#pragma once
#include "BaseScene.h"
class SceneMng;

class TitleScene :
	public BaseScene
{
public:
	TitleScene(SceneMng& mng);
	~TitleScene();
	void Update(const Input& input)override final;
	void Draw()override final;
private:
	int _titleBackH;
	void FadeinUpdate(const Input&);
	void WaitUpdate(const Input&);
	void FadeoutUpdate(const Input&);

	void FadeDrawer();
	void NormalDrawer();

	void (TitleScene::*_updater)(const Input&);
	void (TitleScene::*_drawer)();

	int _fadeCounter;
};

