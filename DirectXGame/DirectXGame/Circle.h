#pragma once
#include "AGameObject.h"
class Circle : public AGameObject
{
public:
	Circle();
	Circle(const Vector3D& position);
	virtual void update() override;
	~Circle();
};

