#pragma once
#include <memory>
#include "Geometry.h"
class SceneMng;
class Input;
class FileSystem;

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
	Configure& GetConfig() { return _config; }
	std::shared_ptr<FileSystem> GetFileSystem() { return _fileSystem; }
private:
	//�����A�R�s�[�A����֎~
	Application();
	Application(const Application&);
	void operator=(const Application&);

	std::unique_ptr<SceneMng> _sceneMng;
	std::unique_ptr<Input> _input;
	std::shared_ptr<FileSystem> _fileSystem;
};

