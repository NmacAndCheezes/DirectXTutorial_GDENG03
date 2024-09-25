#pragma once
#include "Renderer3D.h"

class CubeRenderer : public Renderer3D
{
public:
	CubeRenderer(AGameObject* obj);
	virtual void update() override;
	~CubeRenderer() {}
};

