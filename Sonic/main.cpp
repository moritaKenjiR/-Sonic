#include<windows.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto &app = Application::Instance();
	app.Initialize();
	app.Run();
	app.Terminate();
	return 0;				// èIóπ 
}