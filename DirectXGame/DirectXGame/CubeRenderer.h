#pragma once
#include "Renderer3D.h"

class CubeRenderer : public Renderer3D
{
public:
	CubeRenderer(AGameObject* obj, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~CubeRenderer() {}
};

