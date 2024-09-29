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

	cam = new Camera(this);
	AGameObjectManager::get()->registerAGameObject(cam);

	InputSystem::get()->showCursor(false);
	GraphicsEngine::get()->initialize();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	

#pragma region ConstantBuffer
	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();

	m_cb->load(&cc, sizeof(constant));
#pragma endregion

	Cube* obj = new Cube(Vector3D(1.5f,0,0));
	AGameObjectManager::get()->registerAGameObject(obj);

	obj = new Cube(Vector3D(0, 0, 0));
	AGameObjectManager::get()->registerAGameObject(obj);

	obj = new Cube(Vector3D(-1.5, 0, 0));
	AGameObjectManager::get()->registerAGameObject(obj);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

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

	EngineTime::get()->update();
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
	cam->onFocus();
}

void AppWindow::onKillFocus()
{
	cam->onKillFocus();
}

SwapChain* AppWindow::getSwapChain()
{
	return m_swap_chain;
}

VertexShader* AppWindow::getVertexShader()
{
	return m_vs;
}

PixelShader* AppWindow::getPixelShader()
{
	return m_ps;
}

ConstantBuffer* AppWindow::getConstantBuffer()
{
	return m_cb;
}
