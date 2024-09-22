#pragma once

class AGameObject;
class Component
{
public:
	Component(AGameObject* obj);
	virtual void update() = 0;
	virtual void release() = 0;
	~Component() {}
protected:
	AGameObject* attachedObject = nullptr;
};

