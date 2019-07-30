#pragma once
#include <memory>
#include <vector>
class EventObserver;

class EventQueue
{
public:
	EventQueue();
	~EventQueue();
private:
	std::vector<std::shared_ptr<EventObserver>> _observers;
};

