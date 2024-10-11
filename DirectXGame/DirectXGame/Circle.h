#pragma once
#include "AGameObject.h"
class Circle : public AGameObject
{
public:
	Circle(int segments, float radius);
	Circle(const Vector3D& position, int segments, float radius);
	virtual void update() override;
	~Circle();
};

