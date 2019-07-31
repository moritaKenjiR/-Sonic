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
	void AddEvent(std::shared_ptr<Event> e);
	void AddObserver(std::shared_ptr<EventObserver> ob);
private:

	std::vector<std::shared_ptr<EventObserver>> _observers;
	std::vector<std::shared_ptr<Event>> _events;
};

