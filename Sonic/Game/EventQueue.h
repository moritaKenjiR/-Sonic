#pragma once
#include <memory>
#include <vector>
class Event;
class EventObserver;

class EventQueue
{
	friend Event;
public:
	EventQueue();
	~EventQueue();
	void Notify();
	void AddEvent(Event* e);
	void AddObserver(std::shared_ptr<EventObserver> ob);
private:

	std::vector<std::shared_ptr<EventObserver>> _observers;
	std::vector<Event*> _events;
};

