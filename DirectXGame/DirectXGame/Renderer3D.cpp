#include "Renderer3D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

Renderer3D::Renderer3D(AGameObject* obj) : Component(obj)
{
}

void Renderer3D::update()
{
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Renderer3D::setVertex()
{

}

void Renderer3D::release()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
	m_ib->release();
	delete this;
}

Matrix4x4 Renderer3D::getLocalMatrix()
{
	return Matrix4x4();
}
