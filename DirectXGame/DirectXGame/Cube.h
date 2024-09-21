#pragma once

#include "AGameObject.h"

class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;

class Cube : AGameObject
{
public:
	Cube();
	virtual void update() override;
	~Cube();
	
};

