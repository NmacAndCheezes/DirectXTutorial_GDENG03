#include "Cube.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "CubeRenderer.h"
#include <iostream>

Cube::Cube(std::string name) : AGameObject(name)
{
	CubeRenderer* rend = new CubeRenderer(this);
	this->attachComponent(rend);
}

void Cube::update()
{
	AGameObject::update();

	constant cc;
}

Cube::~Cube()
{
}
