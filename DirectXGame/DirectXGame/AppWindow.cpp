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
#include "CameraManager.h"
#include "Circle.h"

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

#if 0
	Camera* cam2 = new Camera(this, Vector3D(1, 0, -2));
	AGameObjectManager::get()->registerAGameObject(cam2);

	Camera* cam3 = new Camera(this, Vector3D(-1, 0, -2));
	AGameObjectManager::get()->registerAGameObject(cam3);
	
	m_cm = new CameraManager();

	m_cm->registerCamera(cam);
	m_cm->registerCamera(cam2);
	m_cm->registerCamera(cam3);
	m_cm->ChangeCam(1);
#endif
	//InputSystem::get()->addListner(m_cm);
	InputSystem::get()->addListner(this);
	InputSystem::get()->showCursor(false);
	GraphicsEngine::get()->initialize();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, getWidth(), getHeight());

	Circle* qobj = new Circle(Vector3D(0, 0, 2), 10, 1.f);
	AGameObjectManager::get()->registerAGameObject(qobj);

	Cube* cobj = new Cube(Vector3D(0, 0, 2));
	AGameObjectManager::get()->registerAGameObject(cobj);

	cam = new Camera(this, Vector3D(0, 0, -2));
	AGameObjectManager::get()->registerAGameObject(cam);
	InputSystem::get()->addListner(cam);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->m_swap_chain,
		0,
		0, 
		0, 
		1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	AGameObjectManager::get()->update();
	GraphicsEngine::get()->getRenderSystem()->draw(this);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onKeyDown(int key)
{
	if (key == VK_ESCAPE)
	{
		m_is_run = false;
	}
	else
	{
		if (key == ' ')
		{
			Circle* qobj = new Circle(Vector3D(0, 0, 2), 10, 1.f);
			AGameObjectManager::get()->registerAGameObject(qobj);
		}
	}
}

void AppWindow::onFocus()
{
	//m_cm->onFocus();
	InputSystem::get()->addListner(cam);
}

void AppWindow::onKillFocus()
{
	//m_cm->onKillFocus();
	InputSystem::get()->removeListner(cam);
}

SwapChainPtr AppWindow::getSwapChain()
{
	return m_swap_chain;
}

Camera* AppWindow::getCamera()
{
	return cam;
}

float AppWindow::getWidth()
{
	RECT rc = this->getClientWindowRect();
	return rc.right - rc.left;
}

float AppWindow::getHeight()
{
	RECT rc = this->getClientWindowRect();
	return rc.bottom - rc.top;
}
