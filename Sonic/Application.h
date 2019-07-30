#pragma once
#include <memory>
#include "Geometry.h"
#include "System/FileSystem.h"
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
		Size GetScreenSize()const;
		float GetGravity()const;
		float GetJupmPower()const;
	};

	//���ع���ݏ������֐�
	bool Initialize(void);

	void InitializeInput();

	//���ع���݂����s����(�ް�ٰ��)
	void Run(void);

	//�I������
	void Terminate(void);

	Configure _config;
	FileSystem _fileSystem;
	Configure& GetConfig() { return _config; }
	FileSystem& GetFileSystem() { return _fileSystem; }
private:
	//�����A�R�s�[�A����֎~
	Application();
	Application(const Application&);
	void operator=(const Application&);

	std::unique_ptr<SceneMng> _sceneMng;
	std::unique_ptr<Input> _input;
	
};

