#pragma once
#include "Renderer.h"

class CubeRenderer : public Renderer
{
public:
	CubeRenderer();
	virtual void update() override;
	~CubeRenderer() {}
};

