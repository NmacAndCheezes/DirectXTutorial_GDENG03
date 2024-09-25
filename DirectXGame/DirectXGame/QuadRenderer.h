#pragma once
#include "Renderer2D.h"

class QuadRenderer : public Renderer2D
{
public:
	QuadRenderer(AGameObject* obj);
	virtual void update() override;
	~QuadRenderer() {}
};

