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

	//ŠÄ‹ÌßÚ²Ô°‚Ì’Ç‰Á
	void AddPlayer(std::shared_ptr<Player> player);

	//ŠÄ‹ÌßÚ²Ô°‚Ìíœ
	void RemovePlayer(std::shared_ptr<Player> player);

	void SetRange(const Size& stageSize);

	void Update();

	const Position2& GetPosition()const;

	const Rect& GetViewRange()const;
private:
	Position2 _initPos;
	Position2 _pos;
	std::vector<std::shared_ptr<Player>> _players;
};

