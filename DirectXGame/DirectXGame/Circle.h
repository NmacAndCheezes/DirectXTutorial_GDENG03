#pragma once
#include "AGameObject.h"
class Circle : public AGameObject
{
public:
	Circle(int segments, float radius, void* shader_byte_code, size_t size_shader);
	Circle(const Vector3D& position, int segments, float radius, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	~Circle();
};

