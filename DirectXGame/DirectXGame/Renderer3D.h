#pragma once
#include "Renderer.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"

class Renderer3D : public Renderer
{
public:
	Renderer3D(AGameObject* obj, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~Renderer3D() {}

protected:
	IndexBufferPtr m_ib = nullptr;

	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj; //projection matrix
		unsigned int m_time = 0;
	};

};

