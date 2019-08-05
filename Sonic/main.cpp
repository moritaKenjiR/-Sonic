#include<windows.h>
#include "Application.h"

void main()
{
	auto &app = Application::Instance();
	app.Initialize();
	app.Run();
	app.Terminate();
	return;				// èIóπ 
}