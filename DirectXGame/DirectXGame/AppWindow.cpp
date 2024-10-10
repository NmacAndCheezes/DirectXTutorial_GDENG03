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

void AppWindow::spawnCircle(Vector3D pos)
{
	std::cout << "Spawned new circle at " << pos.m_x << ", " << pos.m_y << std::endl;
	Circle* qobj = new Circle(pos);
	m_circle_num++;
	AGameObjectManager::get()->registerAGameObject(qobj, "Circle" + std::to_string(m_circle_num));
	std::cout << "Total circles: " << m_circle_num << std::endl;
}

void AppWindow::destroyCircle()
{
	AGameObjectManager::get()->removeAGameObject("Circle" + std::to_string(m_circle_num));
	m_circle_num--;
	if (m_circle_num < 0) m_circle_num = 0;
	std::cout << "Total circles: " << m_circle_num << std::endl;
	
}

void AppWindow::onCreate()
{
	Window::onCreate();

	cam = new Camera(this, Vector3D(0,0,-2));
	AGameObjectManager::get()->registerAGameObject(cam, "Cam1");
	
#if 0
	Camera* cam2 = new Camera(this, Vector3D(1, 0, -2));
	AGameObjectManager::get()->registerAGameObject(cam2, "Cam2");

	Camera* cam3 = new Camera(this, Vector3D(-1, 0, -2));
	AGameObjectManager::get()->registerAGameObject(cam3, "Cam3");
	
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
	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);	

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	spawnCircle(Vector3D(0,0,0));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->m_swap_chain,
		0,
		0.3f, 
		0.4f, 
		1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	AGameObjectManager::get()->update();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	AGameObjectManager::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	if (isHoldingDownBtn) return;
	isHoldingDownBtn = true;
	if (key == VK_ESCAPE)
	{
		m_is_run = false;
	}

	if (key == ' ')
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		spawnCircle(Vector3D((x - 0.5f) * 2, (y - 0.5f) * 2, 0));
	}
	if (key == VK_BACK)
	{
		destroyCircle();
	}
	if (key == VK_DELETE)
	{
		for (int i = 1; i <= m_circle_num; i++)
		{
			AGameObjectManager::get()->removeAGameObject("Circle" + std::to_string(i));
		}

		m_circle_num = 0;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (!isHoldingDownBtn) return;
	isHoldingDownBtn = false;
	
}

void AppWindow::onFocus()
{
	//cam->onFocus();
}

void AppWindow::onKillFocus()
{
	//cam->onKillFocus();
}

SwapChainPtr AppWindow::getSwapChain()
{
	return m_swap_chain;
}

VertexShaderPtr AppWindow::getVertexShader()
{
	return m_vs;
}

PixelShaderPtr AppWindow::getPixelShader()
{
	return m_ps;
}

ConstantBufferPtr AppWindow::getConstantBuffer()
{
	return m_cb;
}
