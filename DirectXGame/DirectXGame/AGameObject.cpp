#include "AGameObject.h"
#include "Component.h"

AGameObject::AGameObject() : m_position(Vector3D()) {}

AGameObject::AGameObject(const Vector3D& position) : m_position(position) { }

void AGameObject::update()
{
	if (!this->m_isActive) return;
	for (auto c : m_component_list)
	{
		c->update();
	}
}

void AGameObject::attachComponent(Component* component)
{
	m_component_list.push_back(component);
}

void AGameObject::detachComponent(Component* component)
{
	m_component_list.remove(component);
}

void AGameObject::setActive(bool isActive)
{
	this->m_isActive = isActive;
}

bool AGameObject::getActive()
{
	return m_isActive;
}

Vector3D AGameObject::position()
{
	return m_position;
}

Vector3D AGameObject::rotation()
{
	return m_rotation;
}

Vector3D AGameObject::scale()
{
	return m_scale;
}
