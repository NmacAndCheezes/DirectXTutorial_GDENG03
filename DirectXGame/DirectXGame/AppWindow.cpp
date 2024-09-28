#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include <iostream>
#include "EngineTime.h"
#include "AGameObjectManager.h"
#include "CubeRenderer.h"
#include "Cube.h"
#include "Quad.h"

struct vertex 
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant 
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj; //projection matrix
	unsigned int m_time = 0;
};

void AppWindow::onCreate()
{
	Window::onCreate();

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Camera* cam = new Camera(this, "Camera");
	AGameObjectManager::get()->registerAGameObject(cam);
	cam->getLocalPosition().setVector3D(0,0,-2);
	AGameObjectManager::get()->registerCamera(cam);

	InputSystem::get()->showCursor(false);
	GraphicsEngine::get()->initialize();

	Cube* cube = new Cube("Cube");
	AGameObjectManager::get()->registerAGameObject(cube);
	cube->getLocalPosition().setVector3D(0, 0, 2);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	EngineTime::get()->update();
	InputSystem::get()->update();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->m_swap_chain,
		0,
		0.3f, 
		0.4f, 
		1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	AGameObjectManager::get()->update();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
	AGameObjectManager::get()->release();
}

void AppWindow::onFocus()
{
	for (auto i : AGameObjectManager::get()->getCameras())
		i->onFocus();
	//cam->onFocus();
}

void AppWindow::onKillFocus()
{
	for (auto i : AGameObjectManager::get()->getCameras())
		i->onKillFocus();
	//cam->onKillFocus();
}

SwapChain* AppWindow::getSwapChain()
{
	return m_swap_chain;
}
