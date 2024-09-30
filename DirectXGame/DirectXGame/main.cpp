#include "AppWindow.h"
#include "InputSystem.h"


int main()
{
	try
	{
		GraphicsEngine::initialize();
		InputSystem::initialize();
	}
	catch (...) { return -1; }

	{
		try
		{
			AppWindow app;
			while (app.isRun());
		}
		catch (...) {
			InputSystem::destroy();
			GraphicsEngine::destroy();
			return -1;
		}
	}

	InputSystem::destroy();
	GraphicsEngine::destroy();

	return 0;
}