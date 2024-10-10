#pragma once
#include "AGameObject.h"

class Quad : public AGameObject
{
public:
	Quad(void* shader_byte_code, size_t size_shader);
	Quad(const Vector3D& position, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	~Quad();
};

