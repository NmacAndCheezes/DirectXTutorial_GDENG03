#include "Quad.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "QuadRenderer.h"
#include <iostream>

Quad::Quad(void* shader_byte_code, size_t size_shader) : AGameObject()
{
	QuadRenderer* rend = new QuadRenderer(this, shader_byte_code, size_shader);
	this->attachComponent(rend);
}

Quad::Quad(const Vector3D& position, void* shader_byte_code, size_t size_shader) : AGameObject(position)
{
	QuadRenderer* rend = new QuadRenderer(this, shader_byte_code, size_shader);
	this->attachComponent(rend);
}

void Quad::update()
{
	AGameObject::update();
}

Quad::~Quad()
{
}
