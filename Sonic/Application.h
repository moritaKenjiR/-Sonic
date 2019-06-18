#pragma once
#include <memory>
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

	//���ع���ݏ������֐�
	bool Initialize(void);

	void InitializeInput();

	//���ع���݂����s����(�ް�ٰ��)
	void Run(void);

	//�I������
	void Terminate(void);
private:
	//�����A�R�s�[�A����֎~
	Application();
	Application(const Application&);
	void operator=(const Application&);

	std::unique_ptr<SceneMng> _sceneMng;
	std::unique_ptr<Input> _input;
};

