#pragma once
class EventObserver
{
public:
	EventObserver();
	virtual ~EventObserver();
	virtual bool OnNotify(Event * e) = 0;
};

