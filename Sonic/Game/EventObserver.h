#pragma once
#include <memory>
class EventObserver
{
public:
	EventObserver();
	virtual ~EventObserver();
	virtual bool OnNotify(const Event* e) = 0;
};

