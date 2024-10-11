#include "Circle.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "CircleRenderer.h"
#include <iostream>

Circle::Circle(int segments, float radius) : AGameObject()
{
	CircleRenderer* rend = new CircleRenderer(this, segments, radius);
	this->attachComponent(rend);
}

Circle::Circle(const Vector3D& position, int segments, float radius) : AGameObject(position)
{
	CircleRenderer* rend = new CircleRenderer(this, segments, radius);
	this->attachComponent(rend);
}

void Circle::update()
{
	AGameObject::update();
}

Circle::~Circle()
{
}
