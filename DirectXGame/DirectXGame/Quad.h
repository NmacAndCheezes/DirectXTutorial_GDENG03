#pragma once
#include "AGameObject.h"

class Quad : public AGameObject
{
public:
	Quad();
	Quad(const Vector3D& position);
	virtual void update() override;
	~Quad();
};

