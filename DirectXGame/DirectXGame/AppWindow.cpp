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
	GraphicsEngine::get()->init();
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

#if 0
	//rectangle with a rainbow pixel shader.
#if 0
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(1,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(0,1,0),  Vector3D(0,1,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,0,1),  Vector3D(0,0,1) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,0), Vector3D(1,1,0) },
	};
#endif

	//triangle with a rainbow pixel shader
#if 0
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(0.0f,0.5f,0.0f),    Vector3D(1,0,0),  Vector3D(1,0,0) },
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,1,0),  Vector3D(0,1,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),   Vector3D(0,0,1),  Vector3D(0,0,1) },
		//{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,0), Vector3D(1,1,0) },
	};
#endif

	//rectangle with a green pixel shader.
#if 0
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,1,0),  Vector3D(0,1,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(0,1,0),  Vector3D(0,1,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,1,0),  Vector3D(0,1,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(0,1,0), Vector3D(0,1,0) },
	};
#endif

#if 1
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};
#endif

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, // FIRST TRIANGLE
		2,3,0, // SECOND TRIANGLE

		//BACK SIDE
		4,5,6,
		6,7,4,

		//TOP SIDE
		1,6,5,
		5,2,1,

		//BOTTON SIDE
		7,0,3,
		3,4,7,

		//RIGHT SIDE
		3,2,5,
		5,4,3,

		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;


#pragma region VertexShaders and Buffer
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
#pragma endregion

#pragma region PixelShader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
#pragma endregion
#endif

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
