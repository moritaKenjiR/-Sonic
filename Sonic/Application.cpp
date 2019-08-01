#include "Application.h"
#include <DxLib.h>
#include "Scene/SceneMng.h"
#include "Input/Input.h"
#include "Geometry.h"

constexpr auto default_window_width = 1024;
constexpr auto default_window_height = 576;

constexpr float gravity = 0.98f;
constexpr float jump_power = -2.5f;

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
	_input->AddCommand(0, "jump", 0, KEY_INPUT_Z);
	_input->AddCommand(0, "ok", 0, KEY_INPUT_RETURN);
	_input->AddCommand(0, "pause", 0, KEY_INPUT_P);
	_input->AddCommand(0, "forward", 0, KEY_INPUT_Q);
	_input->AddCommand(0, "back", 0, KEY_INPUT_E);
	_input->AddCommand(0, "rotate", 0, KEY_INPUT_R);
	
	for (int i = 0; i < _input->GetConnectedPadCount(); ++i)
	{
		_input->AddCommand(i, "left", 1 + i, PAD_INPUT_LEFT);
		_input->AddCommand(i, "right", 1 + i, PAD_INPUT_RIGHT);
		_input->AddCommand(i, "up", 1 + i, PAD_INPUT_UP);
		_input->AddCommand(i, "down", 1 + i, PAD_INPUT_DOWN);
		_input->AddCommand(i, "ok", 1 + i, PAD_INPUT_8);
		_input->AddCommand(i, "pause", 1 + i, PAD_INPUT_7);
		_input->AddCommand(i, "jump", 1 + i, PAD_INPUT_1);
	}
}

void Application::Run(void)
{
	while (ProcessMessage() == 0)
	{
		ClsDrawScreen();
		_input->Update();
		_sceneMng->Update(*_input);

#ifdef _DEBUG 
		auto fps = GetFPS();
		auto drawCallCount = GetDrawCallCount();
		DrawFormatString(12, 12, 0x000000, "FPS=%f", fps);
		DrawFormatString(10, 10, 0xffffff, "FPS=%f", fps);
		DrawFormatString(12, 32, 0x000000, "DrawCall=%d", drawCallCount);
		DrawFormatString(10, 30, 0xffffff, "DrawCall=%d", drawCallCount);
#endif
		
		ScreenFlip();
	}
}

void Application::Terminate(void)
{
}

Size Application::Configure::GetScreenSize() const
{
	return { default_window_width,default_window_height };
}

float Application::Configure::GetGravity() const
{
	return gravity;
}

float Application::Configure::GetJupmPower() const
{
	return jump_power;
}
