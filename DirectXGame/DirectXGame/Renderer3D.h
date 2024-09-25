#pragma once
#include "Component.h"
#include "Vector3D.h"

class VertexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class IndexBuffer;

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


};

