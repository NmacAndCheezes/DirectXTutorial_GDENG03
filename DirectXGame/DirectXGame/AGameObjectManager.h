#pragma once
#include <unordered_map>
#include "Camera.h"

class AGameObject;

class AGameObjectManager
{
public:
	AGameObjectManager() {}
	void registerAGameObject(AGameObject* obj);
	AGameObject* findGameObject(std::string key);
	void update();
	void release();
	~AGameObjectManager() {}

	void registerCamera(Camera* cam);
	std::list<Camera*> getCameras();

public:
	static AGameObjectManager* get();
private:
	std::unordered_map<std::string, AGameObject*> m_object_list;
	std::list<Camera*> m_cams;
};

