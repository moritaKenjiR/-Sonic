#pragma once
#include "EventObserver.h"

class Event;

class HUD : public EventObserver
{
public:
	HUD();
	~HUD();

	void Update();
	void Draw();
	bool OnNotify(Event* e)override final;
private:
	int _coinH = 0;
	int _score = 0;
	unsigned int _coinNum;
};

