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

	Camera* cam = new Camera(this);
	AGameObjectManager::get()->registerAGameObject(cam);
	
	Camera* cam2 = new Camera(this);
	AGameObjectManager::get()->registerAGameObject(cam2);

	Camera* cam3 = new Camera(this);
	AGameObjectManager::get()->registerAGameObject(cam3);
	
	m_cm = new CameraManager();

	m_cm->registerCamera(cam);
	m_cm->registerCamera(cam2);
	m_cm->registerCamera(cam3);
	m_cm->ChangeCam(1);
	InputSystem::get()->addListner(m_cm);

	InputSystem::get()->showCursor(false);
	GraphicsEngine::get()->initialize();
	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);	

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	Cube* cobj = new Cube(Vector3D(1.5f,0,0));
	AGameObjectManager::get()->registerAGameObject(cobj);

	Quad* qobj = new Quad(Vector3D(0, 0, 0));
	AGameObjectManager::get()->registerAGameObject(qobj);

	cobj = new Cube(Vector3D(-1.5, 0, 0));
	AGameObjectManager::get()->registerAGameObject(cobj);

	qobj = new Quad(Vector3D(-3.0f, 0, 0));
	AGameObjectManager::get()->registerAGameObject(qobj);

	cobj = new Cube(Vector3D(3.0f, 0, 0));
	AGameObjectManager::get()->registerAGameObject(cobj);

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
	AGameObjectManager::get()->release();
}

void AppWindow::onFocus()
{
	m_cm->onFocus();
}

void AppWindow::onKillFocus()
{
	m_cm->onKillFocus();
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
