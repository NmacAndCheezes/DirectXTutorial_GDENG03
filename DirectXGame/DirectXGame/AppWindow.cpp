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
#pragma region VertexShaders and Buffer

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	Circle* qobj = new Circle(Vector3D(0, 0, 2), 10, 1.f, shader_byte_code, size_shader);
	AGameObjectManager::get()->registerAGameObject(qobj);

	Cube* cobj = new Cube(Vector3D(0, 0, 2), shader_byte_code, size_shader);
	AGameObjectManager::get()->registerAGameObject(cobj);

	
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
#pragma endregion

#pragma region PixelShader
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
#pragma endregion

	cam = new Camera(this, Vector3D(0, 0, -2));
	AGameObjectManager::get()->registerAGameObject(cam);
	InputSystem::get()->addListner(cam);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(this->m_ps);
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
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			VertexShaderPtr vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
			Circle* qobj = new Circle(Vector3D(0, 0, 2), 10, 1.f, shader_byte_code, size_shader);
			AGameObjectManager::get()->registerAGameObject(qobj);
			
			GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

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

VertexShaderPtr AppWindow::getVertexShader()
{
	return m_vs;
}

PixelShaderPtr AppWindow::getPixelShader()
{
	return m_ps;
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
