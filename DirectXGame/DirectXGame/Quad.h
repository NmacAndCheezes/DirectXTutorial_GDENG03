#pragma once
#include "AGameObject.h"

class Quad : public AGameObject
{
public:
	Quad(std::string name);
	virtual void update() override;
	~Quad();
};

