#include "Event.h"
#include "EventQueue.h"
#include "EventObserver.h"
#include "Coin.h"
#include "ScoreUpper.h"
#include <algorithm>

EventQueue::EventQueue()
{
}


EventQueue::~EventQueue()
{
}

void EventQueue::Notify()
{
	std::vector<Event*> availableEvents;
	auto inserter = back_inserter(availableEvents);
	copy_if(_events.begin(), _events.end(), inserter, [](Event*& event) {
		return event->EventAvailable();
	});
	for (auto& ob : _observers) 
	{
		for (auto& event : availableEvents) 
		{
			if (ob->OnNotify(event)) 
			{
				event->_eventAvailable = false;
			}
		}
	}
	auto it = remove_if(_events.begin(), _events.end(), [](Event*& event) {
		return !event->IsAvailable();});
	auto itCpy = it;
	for (; itCpy != _events.end(); ++itCpy)
	{
		if ((*itCpy)->_deleteByQueue == true)
		{
			delete (*itCpy);
		}
	}
	_events.erase(it, _events.end());
}

void EventQueue::AddEvent(Event* e)
{
	_events.push_back(e);
}

void EventQueue::AddObserver(std::shared_ptr<EventObserver> ob)
{
	_observers.push_back(ob);
}
