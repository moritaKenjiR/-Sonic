#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::AddPlayer(std::shared_ptr<Player> player)
{
	_players.push_back(player);
}

void Camera::RemovePlayer(std::shared_ptr<Player> player)
{

}
