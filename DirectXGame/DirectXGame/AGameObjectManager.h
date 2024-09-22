#pragma once
#include <list>

class AGameObject;

class AGameObjectManager
{
public:
	AGameObjectManager() {}
	void registerAGameObject(AGameObject* obj);
	void update();
	void release();
	~AGameObjectManager() {}

public:
	static AGameObjectManager* get();
private:
	std::list<AGameObject*> m_object_list;
};

