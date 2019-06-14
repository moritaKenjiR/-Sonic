#include "Application.h"
#include <DxLib.h>
#include "SceneMng.h"
#include "Input.h"
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

	_sceneMngPtr = std::make_unique<SceneMng>();
	
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
	for (int i = 0; i < _input->GetConnectedPadCount(); ++i)
	{
		_input->AddCommand(i, "left", 1 + i, PAD_INPUT_LEFT);
		_input->AddCommand(i, "right", 1 + i, PAD_INPUT_RIGHT);
		_input->AddCommand(i, "up", 1 + i, PAD_INPUT_UP);
		_input->AddCommand(i, "down", 1 + i, PAD_INPUT_DOWN);
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
		for (int i = 0; i < GetJoypadNum() + 1; ++i)
		{
			if (_input->Ispressed(i, "left"))
			{
				pos[i].x -= 5;
			}
			if (_input->Ispressed(i, "right"))
			{
				pos[i].x += 5;
			}
			if (_input->Ispressed(i, "up"))
			{
				pos[i].y -= 5;
			}
			if (_input->Ispressed(i, "down"))
			{
				pos[i].y += 5;
			}

			DrawCircle(pos[i].x, pos[i].y, 40,0xff3030, true);
		}
		ScreenFlip();
	}
}

void Application::Terminate(void)
{
}
