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
#include "Camera.h"
#include <iostream>
#include "AGameObjectManager.h"

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

#pragma region ConstantBuffer
	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();

	m_cb->load(&cc, sizeof(constant));
#pragma endregion
}

void CubeRenderer::update()
{
	Renderer3D::update();

	for (auto cam : AGameObjectManager::get()->getCameras())
	{
		//set vertex shader and pixel shader for the object
		DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
		deviceContext->setVertexShader(m_vs);
		deviceContext->setPixelShader(m_ps);

		constant c = {};

		Matrix4x4 allMatrix; allMatrix.setIdentity();
		Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(attachedObject->getLocalPosition());
		Matrix4x4 scaleMatrix; scaleMatrix.setScale(attachedObject->getLocalScale());
		Vector3D rotation = attachedObject->getLocalRotation();
		Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.Z());
		Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.X());
		Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.Y());

		//Scale --> Rotate --> Transform as recommended order.
		Matrix4x4 rotMatrix; rotMatrix.setIdentity();
		rotMatrix *= zMatrix * yMatrix * xMatrix;
		allMatrix *= scaleMatrix * rotMatrix;
		allMatrix *= translationMatrix;
		c.m_world = allMatrix;

		Matrix4x4 cameraMatrix = cam->getCameraViewMatrix();
		c.m_view = m_local_matrix;

		//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
		float aspectRatio = cam->getAspectRatio();
		c.m_proj.setPerspectiveForLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

		this->m_cb->update(deviceContext, &c);
		deviceContext->setConstantBuffer(m_ps, this->m_cb);
		deviceContext->setIndexBuffer(this->m_ib);
		deviceContext->setVertexBuffer(this->m_vb);

		deviceContext->drawTriangleList(this->m_ib->getSizeIndexList(), 0);
	}
		
}
	
