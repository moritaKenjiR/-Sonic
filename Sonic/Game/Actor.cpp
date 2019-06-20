#include "Actor.h"
#include "Camera.h"


Actor::Actor(const Camera cam):_camera(cam)
{
}

Actor::Actor(const Camera cam,const Vector2f & pos):_camera(cam),_pos(pos)
{
}


Actor::~Actor()
{
}
