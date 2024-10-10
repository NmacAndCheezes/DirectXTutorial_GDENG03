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

QuadRenderer::QuadRenderer(AGameObject* obj, void* shader_byte_code, size_t size_shader) : Renderer2D(obj, shader_byte_code, size_shader)
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

	
	UINT size_list = ARRAYSIZE(vertex_list);
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

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	std::cout << m_vb << std::endl;
	GraphicsEngine::get()->getRenderSystem()->registerRenderer(this);
}


void QuadRenderer::update()
{ 
	Renderer2D::update();
}

void QuadRenderer::draw(AppWindow* target)
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

	cc.m_proj.printMatrix();
	this->m_cb->update(deviceContext, &cc);

	deviceContext->setConstantBuffer(target->getVertexShader(), m_cb);
	deviceContext->setConstantBuffer(target->getPixelShader(), m_cb);

	//deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(m_vb);

	//deviceContext->drawTriangle(this->indexBuffer->getIndexSize(), 0, 0);
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}
