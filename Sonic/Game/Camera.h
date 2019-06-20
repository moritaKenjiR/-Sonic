#pragma once
#include <vector>
#include <memory>
#include "../Geometry.h"
class Player;

class Camera
{
public:
	Camera();
	~Camera();

	//�Ď���ڲ԰�̒ǉ�
	void AddPlayer(std::shared_ptr<Player> player);

	//�Ď���ڲ԰�̍폜
	void RemovePlayer(std::shared_ptr<Player> player);


private:
	Position2 _initPos;
	Position2 _pos;
	std::vector<std::shared_ptr<Player>> _players;
};

