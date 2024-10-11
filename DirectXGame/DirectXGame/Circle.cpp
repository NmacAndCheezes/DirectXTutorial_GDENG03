#include "Circle.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "CircleRenderer.h"
#include <iostream>

Circle::Circle() : AGameObject()
{
	CircleRenderer* rend = new CircleRenderer(this, 50);
	this->attachComponent(rend);
}

Circle::Circle(const Vector3D& position) : AGameObject(position)
{
	CircleRenderer* rend = new CircleRenderer(this, 50);
	this->attachComponent(rend);
}

void Circle::update()
{
	AGameObject::update();
}

Circle::~Circle()
{
}
