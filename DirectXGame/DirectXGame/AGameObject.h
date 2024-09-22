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
	virtual void release();
	virtual void attachComponent(Component* component);
	virtual void detachComponent(Component* component);
	~AGameObject() {}

public:
	Vector3D position();
private:
	std::list<Component*> m_component_list;

protected:
	Vector3D m_position = Vector3D();

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj; //projection matrix
		unsigned int m_time = 0;
	};
};

