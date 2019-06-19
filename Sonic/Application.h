#pragma once
#include <memory>
#include "Geometry.h"
class SceneMng;
class Input;

///���ع���ݑS�̂𐧌䂷��
///�ݸ���ݸ׽
class Application
{
public:
	~Application();
	static Application& Instance()
	{
		static Application Instance;
		return Instance;
	}
	class Configure {
	public:
		Position2 GetScreenSize()const;
	};

	//���ع���ݏ������֐�
	bool Initialize(void);

	void InitializeInput();

	//���ع���݂����s����(�ް�ٰ��)
	void Run(void);

	//�I������
	void Terminate(void);

	Configure _config;
	Configure& GetConfig() { return _config; }
private:
	//�����A�R�s�[�A����֎~
	Application();
	Application(const Application&);
	void operator=(const Application&);

	std::unique_ptr<SceneMng> _sceneMng;
	std::unique_ptr<Input> _input;
};

