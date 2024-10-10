#pragma once
#include "AGameObject.h"

class Component
{
public:
	Component(AGameObject* obj);
	virtual void update() = 0;
	AGameObject* getAttachedGameObject();
	~Component() {}
protected:
	AGameObject* attachedObject = nullptr;
};

