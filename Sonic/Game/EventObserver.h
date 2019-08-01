#pragma once
#include <memory>
#include "Event.h"
class EventObserver
{
public:
	EventObserver();
	virtual ~EventObserver();
	virtual bool OnNotify(Event* e) = 0;
};

