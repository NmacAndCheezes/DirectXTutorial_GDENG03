#pragma once
#include "Renderer2D.h"

class QuadRenderer : public Renderer2D
{
public:
	QuadRenderer(AGameObject* obj, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~QuadRenderer() {}
};

