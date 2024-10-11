#pragma once
#include "Renderer2D.h"
#include "Prerequisites.h"

class CircleRenderer : public Renderer2D
{
public:
	CircleRenderer(AGameObject* obj, int segments, float radius);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~CircleRenderer() {}

private:
	IndexBufferPtr m_ib;
};

