#include "AppWindow.h"
#include "InputSystem.h"
#include "EngineTime.h"

void destroySingletons()
{
	InputSystem::destroy();
	GraphicsEngine::destroy();
	EngineTime::destroy();
}

int main()
{
	try
	{
		GraphicsEngine::initialize();
		InputSystem::initialize();
		EngineTime::initialize();
	}
	catch (...) { return -1; }

	{
		try
		{
			AppWindow app;
			while (app.isRun());
		}
		catch (...) {
			destroySingletons();
			return -1;
		}
	}

	destroySingletons();

	return 0;
}

