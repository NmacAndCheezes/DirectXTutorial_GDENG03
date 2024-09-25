#include "AppWindow.h"
#include "GraphicsEngine.h"

int main()
{
	GraphicsEngine::initialize();
	AppWindow* app = new AppWindow();

	if (app->init()) {
		while (app->isRunning()) {
			app->broadcast();
		}
	}
	delete app;
	
	return 0;
}