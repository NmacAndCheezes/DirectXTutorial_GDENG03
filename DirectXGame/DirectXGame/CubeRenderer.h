#pragma once
#include "Renderer3D.h"

class CubeRenderer : public Renderer3D
{
public:
	CubeRenderer(AGameObject* obj);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~CubeRenderer() {}
};

