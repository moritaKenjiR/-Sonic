#pragma once
#include "../Geometry.h"
class Input;
class Camera;

//Åuπﬁ∞—íÜÇ…ìÆÇ≠Ç‡ÇÃÅväÓíÍ∏◊Ω
class Actor
{
public:
	Actor(const Camera& cam);
	Actor(const Camera& cam, const Position2f& pos);
	virtual ~Actor();
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;

	virtual void OnGround(float grad, float adjustY = -1.0f)= 0;
	virtual void OnDead() = 0;

	virtual void LoadAction(std::string& actPath);

	virtual void Move(float x, float y);
	virtual void Move(const Vector2f& vec);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Vector2f& vec);

	virtual const Vector2f& GetPosition()const;

private:

protected:
	Position2f _pos;
	const Camera& _camera;
};

