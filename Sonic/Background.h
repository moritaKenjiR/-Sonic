#pragma once
#include <memory>
#include <vector>
#include "Geometry.h"
class Camera;

class Stage
{
private:
	const Camera& _camera;
	int _bgH;
public:
	Stage(const Camera& cam);
	~Stage();

	void DataLoad(const char* path);

	void Update();

	void Draw();
};


class Background
{
public:
	enum class LayoutType {
		norepeat,
		repeat,
	};
private:
	const Camera& _camera;
	struct Obj {
		int handle;
		Position2 initpos;
		float rate;
		LayoutType type;
		int repeatX;
		Size size;
		Obj() {};
		Obj(int h,const Position2& p,float r,LayoutType lt,int repX,Size s):
			handle(h), initpos(p),rate(r),type(lt),repeatX(repX),size(s){}
	};
	std::vector<Obj> _bgparts;
public:
	Background(const Camera& cam);
	~Background();

	void Init();

	void AddParts(const char* filepath, const Position2& pos, float rate, bool fromBottom, LayoutType type,Size size, int repeatX);

	void Update();
	void DrawBg();

};

