#include "Cube.h"
#include "Vector3D.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "CubeRenderer.h"
#include <iostream>

Cube::Cube(void* shader_byte_code, size_t size_shader) : AGameObject()
{
	CubeRenderer* rend = new CubeRenderer(this, shader_byte_code, size_shader);
	this->attachComponent(rend);
}

Cube::Cube(const Vector3D& position, void* shader_byte_code, size_t size_shader) : AGameObject(position)
{
	//std::cout << position.m_x << " " << position.m_y << " " << position.m_z << "\n";
	CubeRenderer* rend = new CubeRenderer(this, shader_byte_code, size_shader);
	this->attachComponent(rend);
}

void Cube::update()
{
	AGameObject::update();
}

Cube::~Cube()
{
}
