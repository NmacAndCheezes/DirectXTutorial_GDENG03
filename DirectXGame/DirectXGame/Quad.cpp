#include "Quad.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "QuadRenderer.h"
#include <iostream>

Quad::Quad(std::string name) : AGameObject(name)
{
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
