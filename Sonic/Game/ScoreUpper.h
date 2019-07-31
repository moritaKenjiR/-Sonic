#pragma once
#include "Event.h"
class ScoreUpper :
	public Event
{
public:
	ScoreUpper(EventQueue& eventq,int score);
	~ScoreUpper();
	int GetValue()const override final;

	EventType GetType()const;
	void Update() {};
	void Draw() {};
	const BoxCollider& GetCollider()const;
	void OnCollision(Actor* actor, const BoxCollider& col) {};
private:
	int _score;
};

