#include "Application.h"
#include <DxLib.h>
#include "Scene/SceneMng.h"
#include "Input/Input.h"
#include "Geometry.h"


Application::Application()
{
}


Application::~Application()
{
}

bool Application::Initialize(void)
{
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowText("sonic?");
	SetGraphMode(1024, 576, 16);
	ChangeWindowMode(true);

	_sceneMng = std::make_unique<SceneMng>();
	
	InitializeInput();
	return false;
}

void Application::InitializeInput()
{
	_input = std::make_unique<Input>();
	_input->AddCommand(0, "left", 0, KEY_INPUT_LEFT);
	_input->AddCommand(0, "right", 0, KEY_INPUT_RIGHT);
	_input->AddCommand(0, "up", 0, KEY_INPUT_UP);
	_input->AddCommand(0, "down", 0, KEY_INPUT_DOWN);
	_input->AddCommand(0, "ok", 0, KEY_INPUT_RETURN);
	_input->AddCommand(0, "pause", 0, KEY_INPUT_P);
	for (int i = 0; i < _input->GetConnectedPadCount(); ++i)
	{
		_input->AddCommand(i, "left", 1 + i, PAD_INPUT_LEFT);
		_input->AddCommand(i, "right", 1 + i, PAD_INPUT_RIGHT);
		_input->AddCommand(i, "up", 1 + i, PAD_INPUT_UP);
		_input->AddCommand(i, "down", 1 + i, PAD_INPUT_DOWN);
		_input->AddCommand(i, "ok", 1 + i, PAD_INPUT_8);
		_input->AddCommand(i, "pause", 1 + i, PAD_INPUT_7);
	}
}

void Application::Run(void)
{
	Position2 pos[2];
	pos[0] = { 500,300 };
	pos[1] = { 500,300 };

	while (ProcessMessage() == 0)
	{
		ClsDrawScreen();
		_input->Update();
		_sceneMng->Update(*_input);
		
		ScreenFlip();
	}
}

void Application::Terminate(void)
{
}

Position2 Application::Configure::GetScreenSize() const
{
	return { 1024,576 };
}
