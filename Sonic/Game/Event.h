#pragma once

class Actor;

enum class EventType {
	coin = 1,
	ultimate=4,
	goal = 6,
};

class Event
{
public:
	Event();
	virtual ~Event();
	bool IsAvailable()const;
	virtual EventType GetType()const = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual const BoxCollider& GetCollider()const = 0;
	virtual void OnCollision(Actor* actor, const BoxCollider& col) = 0;
protected:
	bool _isAvailable = true;
};

