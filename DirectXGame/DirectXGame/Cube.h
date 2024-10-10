#pragma once

#include "AGameObject.h"

class Cube : public AGameObject
{
public:
	Cube(void* shader_byte_code, size_t size_shader);
	Cube(const Vector3D& position, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	~Cube();
};

