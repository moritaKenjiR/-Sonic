#pragma once
#include "BaseScene.h"
class SceneMng;

class TitleScene :
	public BaseScene
{
public:
	TitleScene(SceneMng& mng);
	~TitleScene();
	void Update( Input& input)override final;
	void Draw()override final;
private:
	int _titleBackH;
	void FadeinUpdate( Input&);
	void WaitUpdate( Input&);
	void FadeoutUpdate( Input&);

	void FadeDrawer();
	void NormalDrawer();

	void (TitleScene::*_updater)( Input&);
	void (TitleScene::*_drawer)();

	int _fadeCounter;
};

