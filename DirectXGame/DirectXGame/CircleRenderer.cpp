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

CircleRenderer::CircleRenderer(AGameObject* obj, int segments, float radius) 
	: Renderer2D(obj)
{
	std::vector<vertex> vertex_list;
	vertex_list.push_back({ Vector3D(0.f, 0.f, 0.0f), Vector3D(1,1,1), Vector3D(1,1,1) });
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		vertex_list.push_back({ Vector3D(x, y, 0.0f), Vector3D(1,1,1), Vector3D(1,1,1) }); // Assuming a simple Vertex structure
	}
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	UINT size_list = vertex_list.size();
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list.data(), sizeof(vertex), size_list, shader_byte_code, size_shader);
	std::cout << shader_byte_code << " ," << size_shader << std::endl;

#pragma region PixelShader
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
#pragma endregion

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

	GraphicsEngine::get()->getRenderSystem()->registerRenderer(this);
}


void CircleRenderer::update()
{

}

void CircleRenderer::draw(AppWindow* target)
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

	//cc.m_proj.printMatrix();
	deviceContext->setConstantBuffer(m_vs, m_cb);
	deviceContext->setConstantBuffer(m_ps, m_cb);

	//deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(m_vb);

	//deviceContext->drawTriangle(this->indexBuffer->getIndexSize(), 0, 0);
	deviceContext->setIndexBuffer(m_ib);
	// FINALLY DRAW THE TRIANGLE
	deviceContext->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	//attachedObject->position().printVector();


}
