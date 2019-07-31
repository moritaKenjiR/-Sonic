#include "ScoreUpper.h"
#include "../Geometry.h"
#include "../Collision.h"

ScoreUpper::ScoreUpper(EventQueue& eventq,int score):Event(eventq),_score(score)
{
	_deleteByQueue = true;
}


ScoreUpper::~ScoreUpper()
{
}

int ScoreUpper::GetValue() const
{
	return _score;
}

EventType ScoreUpper::GetType() const
{
	return EventType::score;
}

const BoxCollider & ScoreUpper::GetCollider() const
{
	BoxCollider bc(Rect(0, 0, 0, 0));
	return bc;
}
