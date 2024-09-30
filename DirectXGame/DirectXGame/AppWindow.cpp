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
	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);	

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	Quad* obj = new Quad(Vector3D(1.5f,0,0));
	AGameObjectManager::get()->registerAGameObject(obj);

	obj = new Quad(Vector3D(0, 0, 0));
	AGameObjectManager::get()->registerAGameObject(obj);

	obj = new Quad(Vector3D(-1.5, 0, 0));
	AGameObjectManager::get()->registerAGameObject(obj);

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

	EngineTime::get()->update();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
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
