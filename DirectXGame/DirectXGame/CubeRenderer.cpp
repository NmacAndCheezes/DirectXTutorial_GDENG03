#include "CubeRenderer.h"
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

CubeRenderer::CubeRenderer(AGameObject* obj) : Renderer3D(obj)
{
#if 1
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ Vector3D(-0.5f ,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0)},
		{ Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};
#endif
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	UINT size_list = ARRAYSIZE(vertex_list);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

#pragma region PixelShader
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
#pragma endregion
#if 0
	for (int i = 0; i < size_list; i++)
	{
		Vector3D position = vertex_list[i].position;

		position.m_x += obj->position().m_x;
		position.m_y += obj->position().m_y;
		position.m_z += obj->position().m_z;

		vertex_list[i].position = position;
		//std::cout << attachedObject->posX() << " " << attachedObject->posY() << " " << attachedObject->posZ() << " " << "\n";
	}
#endif

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

	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	GraphicsEngine::get()->getRenderSystem()->registerRenderer(this);
}

void CubeRenderer::update()
{
	Renderer3D::update();
}

void CubeRenderer::draw(AppWindow* target)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContextPtr deviceContext = graphEngine->getRenderSystem()->getImmediateDeviceContext();

	constant cc;

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getAttachedGameObject()->position());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getAttachedGameObject()->scale());
	Vector3D rotation = this->getAttachedGameObject()->rotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(zMatrix.multiplyTo(yMatrix.multiplyTo(xMatrix)));
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = target->getCamera()->getViewMatrix();
	cc.m_view = cameraMatrix;

	if (target->getCamera()->getCameraState()) //isPerspective
	{
		float aspectRatio = (float)target->getWidth() / (float)target->getHeight();
		cc.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	}
	else
	{
		cc.m_proj.setOrthoLH(target->getWidth() / 400.0f, target->getHeight() / 400.0f, -4.0f, 4.0f);
	}

	this->m_cb->update(deviceContext, &cc);

	deviceContext->setVertexShader(this->m_vs);
	deviceContext->setPixelShader(this->m_ps);

	deviceContext->setConstantBuffer(this->m_vs, m_cb);
	deviceContext->setConstantBuffer(this->m_ps, m_cb);

	//deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(m_vb);

	//deviceContext->drawTriangle(this->indexBuffer->getIndexSize(), 0, 0);
	Renderer::draw(target);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}
