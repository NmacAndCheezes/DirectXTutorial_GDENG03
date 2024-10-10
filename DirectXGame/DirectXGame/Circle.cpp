#include "Circle.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "CircleRenderer.h"
#include <iostream>

Circle::Circle(int segments, float radius, void* shader_byte_code, size_t size_shader) : AGameObject()
{
	CircleRenderer* rend = new CircleRenderer(this, shader_byte_code, size_shader, segments, radius);
	this->attachComponent(rend);
}

Circle::Circle(const Vector3D& position, int segments, float radius, void* shader_byte_code, size_t size_shader) : AGameObject(position)
{
	CircleRenderer* rend = new CircleRenderer(this, shader_byte_code, size_shader, segments, radius);
	this->attachComponent(rend);
}

void Circle::update()
{
	AGameObject::update();
}

Circle::~Circle()
{
}
