#pragma once
#include "Component.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"
class AppWindow;
class AGameObject;

class Renderer : public Component
{
public:
	Renderer(AGameObject* obj, void* shader_byte_code, size_t size_shader);
	virtual void draw(AppWindow* target);
	~Renderer() {}
	
protected:
	Matrix4x4 transform_matrix;
	VertexBufferPtr m_vb = nullptr;
	ConstantBufferPtr m_cb = nullptr;

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj; //projection matrix
		unsigned int m_time = 0;
	};
};

