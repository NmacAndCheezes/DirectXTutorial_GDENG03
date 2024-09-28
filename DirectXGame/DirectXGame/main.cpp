#include "AppWindow.h"
#include "GraphicsEngine.h"

int main()
{
	GraphicsEngine::initialize();
	AppWindow* app = new AppWindow();

	if (app->init(1024, 768)) {
		while (app->isRunning()) {
			app->broadcast();
		}
	}
	delete app;
	
	return 0;
}