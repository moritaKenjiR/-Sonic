#pragma once
class EventQueue;
class Actor;
class BoxCollider;

enum class EventType {
	coin = 1,
	ultimate = 4,
	goal = 6,
	score = 255
};

class Event
{
	friend EventQueue;
public:
	Event(EventQueue& eventq);
	virtual ~Event();
	bool IsAvailable()const;
	bool EventAvailable()const;
	virtual int GetValue()const { return 0; };

	virtual EventType GetType()const = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual const BoxCollider& GetCollider()const = 0;
	virtual void OnCollision(Actor* actor, const BoxCollider& col) = 0;
protected:
	bool _isAvailable = true;
	bool _eventAvailable = true;
	bool _deleteByQueue = false;
	EventQueue& _eventQueue;
};

