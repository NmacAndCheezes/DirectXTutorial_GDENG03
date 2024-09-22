#pragma once
#include "Renderer.h"

class CubeRenderer : public Renderer
{
public:
	CubeRenderer(AGameObject* obj);
	virtual void update() override;
	~CubeRenderer() {}
};

