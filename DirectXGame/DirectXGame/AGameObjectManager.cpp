#include "AGameObjectManager.h"
#include "AGameObject.h"

void AGameObjectManager::registerAGameObject(AGameObject* obj)
{
	m_object_list.push_back(obj);
}

void AGameObjectManager::update()
{
	for (auto obj : m_object_list)
	{
		if (!obj->getActive()) continue;
		obj->update();
	}
}

void AGameObjectManager::release()
{
	for (auto i : m_object_list)
	{
		i->release();
	}

	m_object_list.clear();
}

AGameObjectManager* AGameObjectManager::get()
{
	static AGameObjectManager manager;
	return &manager;
}
