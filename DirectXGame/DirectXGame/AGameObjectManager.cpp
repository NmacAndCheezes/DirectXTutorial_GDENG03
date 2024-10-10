#include "AGameObjectManager.h"
#include "AGameObject.h"

void AGameObjectManager::registerAGameObject(AGameObject* obj, std::string name)
{
	std::cout << "registered object " << name << std::endl;
	m_object_list.insert({name, obj});
}

void AGameObjectManager::removeAGameObject(std::string name)
{
	std::cout << "removed object " << name << std::endl;
	m_object_list.erase(name);
}

void AGameObjectManager::update()
{
	for (auto obj : m_object_list)
	{
		AGameObject* aObj = obj.second;
		if (!aObj->getActive()) continue;
		aObj->update();
	}
}

void AGameObjectManager::release()
{
	for (auto i : m_object_list)
	{
		AGameObject* aObj = i.second;
		aObj->release();
	}

	m_object_list.clear();
}

AGameObjectManager* AGameObjectManager::get()
{
	static AGameObjectManager manager;
	return &manager;
}
