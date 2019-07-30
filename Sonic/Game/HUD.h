#pragma once
#include "EventObserver.h"

class HUD : public EventObserver
{
public:
	HUD();
	~HUD();

	void Update();
	void Draw();
	bool OnNotify(Event * e)override final;
private:
	int _coinH;
	unsigned int _coinNum;
};

