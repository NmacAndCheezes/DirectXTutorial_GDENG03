#include "AGameObject.h"
#include "Component.h"

AGameObject::AGameObject() : m_position(Vector3D()) {}

AGameObject::AGameObject(const Vector3D& position) : m_position(position) { }

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

Vector3D AGameObject::position()
{
	return m_position;
}
