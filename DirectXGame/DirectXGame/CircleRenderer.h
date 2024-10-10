#pragma once
#include "Renderer2D.h"
#include "Prerequisites.h"

class CircleRenderer : public Renderer2D
{
public:
	CircleRenderer(AGameObject* obj, int segments);
	virtual void update() override;
	~CircleRenderer() {}

private:
	IndexBufferPtr m_ib;
};

