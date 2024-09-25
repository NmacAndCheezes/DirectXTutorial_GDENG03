#pragma once

#include "AGameObject.h"

class Cube : public AGameObject
{
public:
	Cube();
	Cube(const Vector3D& position);
	virtual void update() override;
	~Cube();
};

