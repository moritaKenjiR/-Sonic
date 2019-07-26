#pragma once
#include <vector>
#include <map>
#include "../Geometry.h"

enum class HitRectType {
	none,
	attack,
	damage,
	push,
};

struct ActionRect {
	HitRectType type;
	Rect rc;
};

struct CutData {
	Rect cutrect;
	Position2 center;
	int duration;
	std::vector<ActionRect> actrect;
};

struct Action {
	char isLoop;
	std::vector<CutData> cutdata;
	unsigned int totalDuration;
};


using ActionSet_t =  std::map<std::string, Action>;
