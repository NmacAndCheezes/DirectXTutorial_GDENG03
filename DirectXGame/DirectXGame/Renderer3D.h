#pragma once
#include "Renderer.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"

class Renderer3D : public Renderer
{
public:
	Renderer3D(AGameObject* obj);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~Renderer3D() {}

protected:
	IndexBufferPtr m_ib = nullptr;
};

