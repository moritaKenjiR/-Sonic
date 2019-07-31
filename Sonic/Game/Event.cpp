#include "Event.h"



Event::Event(EventQueue& eventq):_eventQueue(eventq)
{
}


Event::~Event()
{
}

bool Event::IsAvailable() const
{
	return _isAvailable;
}

bool Event::EventAvailable() const
{
	return _eventAvailable;
}
