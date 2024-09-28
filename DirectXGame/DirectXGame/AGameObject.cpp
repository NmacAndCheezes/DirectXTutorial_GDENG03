#include "AGameObject.h"
#include "Component.h"

AGameObject::AGameObject(std::string name) :
	m_name(name),
	m_local_position(Vector3D()),
	m_local_rotation(Vector3D()),
	m_local_scale(Vector3D(1,1,1))
{}

void AGameObject::update()
{
	for (auto c : m_component_list)
	{
		c->update();
	}
}

void AGameObject::release()
{
	for (auto c : m_component_list)
	{
		c->release();
	}
	m_component_list.clear();
}

void AGameObject::attachComponent(Component* component)
{
	m_component_list.push_back(component);
}

void AGameObject::detachComponent(Component* component)
{
	m_component_list.remove(component);
}

std::string AGameObject::getName()
{
	return m_name;
}

Vector3D AGameObject::getLocalPosition()
{
	return m_local_rotation;
}

Vector3D AGameObject::getLocalRotation()
{
	return m_local_rotation;
}

Vector3D AGameObject::getLocalScale()
{
	return m_local_scale;
}
