#include "AGameObjectManager.h"
#include "AGameObject.h"
#include <iostream>

void AGameObjectManager::registerAGameObject(AGameObject* obj)
{
	for (auto o : m_object_list)
	{
		if (o.first == obj->getName()) { std::cout << "object has the same name" << std::endl; return; }
	}

	m_object_list.insert(make_pair(obj->getName(), obj));
}

AGameObject* AGameObjectManager::findGameObject(std::string key)
{
	for (auto obj : m_object_list)
	{
		if (obj.first == key) { std::cout << "find object successful" << std::endl; return obj.second; }
	}

	return nullptr;
}

void AGameObjectManager::update()
{
	for (auto obj : m_object_list)
	{
		obj.second->update();
	}
}

void AGameObjectManager::release()
{
	for (auto i : m_object_list)
	{
		i.second->release();
	}

	m_object_list.clear();
}

void AGameObjectManager::registerCamera(Camera* cam)
{
	for (auto c : m_cams)
	{
		if (c == cam) return;
	}

	m_cams.push_back(cam);
}

std::list<Camera*> AGameObjectManager::getCameras()
{
	return m_cams;
}

AGameObjectManager* AGameObjectManager::get()
{
	static AGameObjectManager manager;
	return &manager;
}
