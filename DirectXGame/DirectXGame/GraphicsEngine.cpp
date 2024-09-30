#include "GraphicsEngine.h"
#include "RenderSystem.h"

#include <string>
#include <iostream>
#include <exception>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("GraphicsEngine was not created"); }
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}


GraphicsEngine* GraphicsEngine::get()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
}

void GraphicsEngine::destroy()
{
	if (!GraphicsEngine::sharedInstance) return;
	delete GraphicsEngine::sharedInstance;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::sharedInstance = nullptr;
	delete m_render_system;
}

