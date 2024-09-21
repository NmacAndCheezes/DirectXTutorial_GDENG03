#pragma once

class AGameObject;
class Component
{
public:
	Component() {}
	Component(AGameObject* obj);
	virtual void update() = 0;
	virtual void release() = 0;
	~Component() {}
private:
	AGameObject* attachedObject = nullptr;
};

