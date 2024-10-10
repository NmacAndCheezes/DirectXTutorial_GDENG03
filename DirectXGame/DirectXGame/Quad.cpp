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
	QuadRenderer* rend = new QuadRenderer(this);
	this->attachComponent(rend);
}

void Quad::update()
{
	AGameObject::update();
}

Quad::~Quad()
{
}
