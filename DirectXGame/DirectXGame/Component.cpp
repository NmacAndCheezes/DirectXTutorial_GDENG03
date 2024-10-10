#include "Component.h"
#include "AGameObject.h"

Component::Component(AGameObject* obj) : attachedObject(obj) {}

AGameObject* Component::getAttachedGameObject()
{
	return attachedObject;
}
