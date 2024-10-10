#include "CircleRenderer.h"
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
#include <vector>

CircleRenderer::CircleRenderer(AGameObject* obj, int segments) : Renderer2D(obj)
{
#if 0
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

	std::vector<vertex> vertex_list;
	vertex_list.push_back({ Vector3D(0.f, 0.f, 0.0f), Vector3D(1,1,1), Vector3D(1,1,1) });
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = 0.1f * cosf(theta);
		float y = 0.1f * sinf(theta);
		vertex_list.push_back({ Vector3D(x, y, 0.0f), Vector3D(1,1,1), Vector3D(1,1,1) }); // Assuming a simple Vertex structure
	}


	UINT size_list = vertex_list.size();
	for (int i = 0; i < size_list; i++)
	{
		Vector3D position = vertex_list[i].position;

		position.m_x += attachedObject->position().m_x;
		position.m_y += attachedObject->position().m_y;
		position.m_z += attachedObject->position().m_z;

		vertex_list[i].position = position;
		//std::cout << attachedObject->posX() << " " << attachedObject->posY() << " " << attachedObject->posZ() << " " << "\n";
	}

	std::vector<unsigned int> index_list;
	for (int i = 1; i <= segments; i++)
	{
		if (i != segments)
		{
			index_list.push_back(0);
			index_list.push_back(i + 1);
			index_list.push_back(i);
		}
		else
		{
			index_list.push_back(0);
			index_list.push_back(1);
			index_list.push_back(segments);
		}
	}

	UINT size_index_list = index_list.size();
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list.data(), size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;


#pragma region VertexShaders and Buffer
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list.data(), sizeof(vertex), size_list, shader_byte_code, size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
#pragma endregion

#pragma region PixelShader
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
#pragma endregion
}


void CircleRenderer::update()
{
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}
