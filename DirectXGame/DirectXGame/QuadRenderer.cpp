#include "QuadRenderer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "AGameObject.h"
#include <iostream>

QuadRenderer::QuadRenderer(AGameObject* obj) : Renderer2D(obj)
{
#if 1
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ Vector3D(-0.5f ,-0.5f,0.0f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0)},
		{ Vector3D(-0.5f,0.5f,0.0f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,0.0f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.0f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },
	};
#endif

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);
	for (int i = 0; i < size_list; i++)
	{
		Vector3D position = vertex_list[i].position;

		position.m_x += attachedObject->position().m_x;
		position.m_y += attachedObject->position().m_y;
		position.m_z += attachedObject->position().m_z;

		vertex_list[i].position = position;
		//std::cout << attachedObject->posX() << " " << attachedObject->posY() << " " << attachedObject->posZ() << " " << "\n";
	}

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
}


void QuadRenderer::update()
{ 
	Renderer2D::update();
}
