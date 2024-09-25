#include "Quad.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "QuadRenderer.h"
#include <iostream>

Quad::Quad() : AGameObject()
{
	QuadRenderer* rend = new QuadRenderer(this);
	this->attachComponent(rend);
}

Quad::Quad(const Vector3D& position) : AGameObject(position)
{
	//std::cout << position.m_x << " " << position.m_y << " " << position.m_z << "\n";
	QuadRenderer* rend = new QuadRenderer(this);
	this->attachComponent(rend);
}

void Quad::update()
{
	AGameObject::update();

	constant cc;
}

Quad::~Quad()
{
}
