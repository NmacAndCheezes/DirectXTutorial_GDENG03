#pragma once
#include <list>

class Component;

class AGameObject
{
public:
	AGameObject() {}
	virtual void update();
	virtual void release();
	virtual void attachComponent(Component* component);
	virtual void detachComponent(Component* component);
	~AGameObject() {}

private:
	std::list<Component*> m_component_list;
};

