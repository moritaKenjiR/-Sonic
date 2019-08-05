#include "Mantis.h"
#include "Player.h"
#include <DxLib.h>
#include "../Application.h"
#include "../System/ImageLoader.h"
#include "../Ground.h"

constexpr int mantisspeed = 2;
constexpr int jump_interval = 60;

Mantis::Mantis(const Camera& cam, const Player& player, const Ground& ground, EventQueue& eventq, int x, int y) :
	Enemy(cam, player,ground,eventq, Position2f(x, y), mantisspeed)
{
	std::string actPath = "action/mantis.act";
	LoadAction(actPath);

	AimPlayer();
	_currentActionName = "idle";
	_currentIndex = 0;
	_collider = _actionSet["idle"].cutdata[0].cutrect;
	_updater = &Mantis::NormalUpdate;

	_vel = Vector2f(0, 0);
	_jumpTime = 0;
}


Mantis::~Mantis()
{
}

void Mantis::LoadAction(std::string & actPath)
{
	int ActPath = FileRead_open(actPath.c_str());

	float version;
	FileRead_read(&version, sizeof(version), ActPath);

	int imgfilepathlen = 0;
	FileRead_read(&imgfilepathlen, sizeof(imgfilepathlen), ActPath);

	std::string imgFilePath;
	imgFilePath.resize(imgfilepathlen);
	FileRead_read(&imgFilePath[0], imgfilepathlen, ActPath);

	imgFilePath = GetFolderPath(actPath) + imgFilePath;
	ImageData data;
	Application::Instance().GetFileSystem()->Load(imgFilePath.c_str(), data);
	atlasImageH = data.GetHandle();

	int actionCount = 0;
	FileRead_read(&actionCount, sizeof(actionCount), ActPath);
	for (int i = 0; i < actionCount; ++i) {
		int actionnamesize = 0;
		FileRead_read(&actionnamesize, sizeof(actionnamesize), ActPath);
		std::string actionname;
		actionname.resize(actionnamesize);
		FileRead_read(&actionname[0], actionnamesize, ActPath);

		char loop;
		FileRead_read(&loop, sizeof(loop), ActPath);
		_actionSet[actionname].isLoop = loop;
		int cutdatacount = 0;
		FileRead_read(&cutdatacount, sizeof(cutdatacount), ActPath);
		for (int j = 0; j < cutdatacount; ++j)
		{
			CutData cd = {};
			Rect cutrect;
			Position2 center;
			int duration;

			FileRead_read(&cd.cutrect, sizeof(cd.cutrect), ActPath);
			FileRead_read(&cd.center, sizeof(cd.center), ActPath);
			FileRead_read(&cd.duration, sizeof(cd.duration), ActPath);

			int actcount = 0;
			FileRead_read(&actcount, sizeof(actcount), ActPath);
			if (actcount > 0) {
				cd.actrects.resize(actcount);
				for (auto& actrect : cd.actrects) {
					FileRead_read(&actrect, sizeof(actrect), ActPath);
				}
			}
			_actionSet[actionname].cutdata.emplace_back(cd);
			_actionSet[actionname].totalDuration += cd.duration;
		}
	}
	FileRead_close(ActPath);
}

void Mantis::Update(const Input &)
{
	//if (!_isAvailable) return;
	++_frame;
	
	_collider.GetRect().center = _pos.ToIntVec() + Position2(-50, -120);
	(this->*_updater)();
	Move(_vel);
}

void Mantis::Draw()
{
	//if (!_isAvailable) return;
	if (_frame >= _actionSet[_currentActionName].totalDuration)
	{
		_frame = 0;
		AimPlayer();
	}
	Position2 offset = _camera.GetOffset();
	DrawRectRotaGraph2(_collider.GetRect().center.x - offset.x, _collider.GetRect().center.y - offset.y,
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.Left(),
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.Top(),
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.size.w,
		_actionSet[_currentActionName].cutdata[(_frame / _actionSet[_currentActionName].cutdata[0].duration)].cutrect.size.h,
		_isLeft ? 0 : 0,
		0,
		4.0f, 0, atlasImageH, true, _isLeft);
}

void Mantis::OnGround(float grad, float adjustY)
{
}

void Mantis::OnDead()
{
	_isAvailable = false;
}

void Mantis::NormalUpdate()
{
	++_jumpTime;
	if (_jumpTime >= jump_interval)
	{
		_vel.y = -12.0f;
		_jumpTime = 0;
		_updater = &Mantis::JumpUpdate;
	}
}

void Mantis::JumpUpdate()
{
	_vel.y += 0.4f;
	float tmp;
	if (abs(_pos.y - _ground.GetCurrentGroundY(tmp)) < 8)
	{
		_vel.y = 0;
		_updater = &Mantis::NormalUpdate;
	}
}

std::shared_ptr<Enemy> Mantis::MakeClone()
{
	auto ret =  std::make_shared<Mantis>(*this);
	ret->_isAvailable = true;
	return ret;
}
