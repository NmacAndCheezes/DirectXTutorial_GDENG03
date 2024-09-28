#pragma once

#include "AGameObject.h"

class Cube : public AGameObject
{
public:
	Cube(std::string name);
	virtual void update() override;
	~Cube();
};

