#pragma once
#include <list>
#include "Matrix4x4.h"

class Component;

class AGameObject
{
public:
	AGameObject();
	AGameObject(const Vector3D& position);
	virtual void update();
	virtual void attachComponent(Component* component);
	virtual void detachComponent(Component* component);
	~AGameObject() {}

	void setActive(bool isActive);
	bool getActive();
public:
	Vector3D position();
	Vector3D rotation();
	Vector3D scale();
private:
	std::list<Component*> m_component_list;

protected:
	Vector3D m_position = Vector3D();
	Vector3D m_rotation = Vector3D();
	Vector3D m_scale = Vector3D(1,1,1);

	

	bool m_isActive = true;
};

