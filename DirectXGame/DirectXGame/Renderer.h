#pragma once
#include "Component.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"
class AppWindow;
class AGameObject;

class Renderer : public Component
{
public:
	Renderer(AGameObject* obj);
	virtual void draw(AppWindow* target);
	~Renderer() {}
	
protected:
	Matrix4x4 transform_matrix;
	VertexBufferPtr m_vb = nullptr;
	ConstantBufferPtr m_cb = nullptr;
	VertexShaderPtr m_vs = NULL;
	PixelShaderPtr m_ps = NULL;
	
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

