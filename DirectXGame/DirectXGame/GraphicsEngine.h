#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
class GraphicsEngine
{
public:
	bool init();
	bool release();
	RenderSystem* getRenderSystem();
public: //singleton
	static GraphicsEngine* get();
	static void initialize();
	static void destroy();
	
private:
	static GraphicsEngine* sharedInstance;
	GraphicsEngine() {}
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};
	~GraphicsEngine() {}

private:
	RenderSystem* m_render_system = nullptr;
};

