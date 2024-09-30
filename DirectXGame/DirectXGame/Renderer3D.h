#pragma once
#include "Component.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"

class Renderer3D : public Component
{
public:
	Renderer3D(AGameObject* obj);
	virtual void update() override;
	void setVertex();
	virtual void release() override;
	~Renderer3D() {}

protected:
	VertexBuffer* m_vb = nullptr;
	VertexShader* m_vs = nullptr;
	PixelShader* m_ps = nullptr;
	IndexBuffer* m_ib = nullptr;

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

