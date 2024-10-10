#pragma once
#include <map>
#include <string>
class AGameObject;

class AGameObjectManager
{
public:
	AGameObjectManager() {}
	void registerAGameObject(AGameObject* obj, std::string name);
	void removeAGameObject(std::string name);
	void update();
	void release();
	~AGameObjectManager() {}

public:
	static AGameObjectManager* get();
private:
	std::map<std::string, AGameObject*> m_object_list;
};

