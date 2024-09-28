#pragma once
#include <list>
#include "Matrix4x4.h"
#include <string>

class Component;

class AGameObject
{
public:
	AGameObject(std::string name);
	virtual void update();
	virtual void release();
	virtual void attachComponent(Component* component);
	virtual void detachComponent(Component* component);
	~AGameObject() {}

public:
	std::string getName();
	Vector3D getLocalPosition();
	Vector3D getLocalRotation();
	Vector3D getLocalScale();

private:
	std::list<Component*> m_component_list;
	std::string m_name;
protected:
	Vector3D m_local_position = Vector3D();
	Vector3D m_local_rotation = Vector3D();
	Vector3D m_local_scale = Vector3D();

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj; //projection matrix
		unsigned int m_time = 0;
	};
};

