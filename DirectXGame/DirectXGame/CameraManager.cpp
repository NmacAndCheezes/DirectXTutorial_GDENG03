#include "CameraManager.h"
#include "InputSystem.h"
#include "Camera.h"

CameraManager::CameraManager() : currentCam(0) 
{
}
CameraManager::CameraManager(int initialCam) : currentCam(initialCam) 
{
}

CameraManager::~CameraManager()
{
}


void CameraManager::onKeyDown(int key)
{
	if (key == 'C' && !isHoldingC)
	{
		isHoldingC = true;
		ChangeCam();
	}
	else
		camList[currentCam]->onKeyDown(key);
}

void CameraManager::onKeyUp(int key)
{
	if (key == 'C' && isHoldingC)
	{
		isHoldingC = false;
	}
	else
		camList[currentCam]->onKeyUp(key);
}

void CameraManager::onMouseMove(const Point& mouse_pos)
{
	camList[currentCam]->onMouseMove(mouse_pos);
}

void CameraManager::onLeftMouseDown(const Point& delta_mouse_pos)
{
	camList[currentCam]->onLeftMouseDown(delta_mouse_pos);
}

void CameraManager::onLeftMouseUp(const Point& delta_mouse_pos)
{
	camList[currentCam]->onLeftMouseUp(delta_mouse_pos);
}

void CameraManager::onRightMouseDown(const Point& delta_mouse_pos)
{
	camList[currentCam]->onRightMouseDown(delta_mouse_pos);
}

void CameraManager::onRightMouseUp(const Point& delta_mouse_pos)
{
	camList[currentCam]->onRightMouseUp(delta_mouse_pos);
}

void CameraManager::onFocus()
{
	InputSystem::get()->addListner(this);
}

void CameraManager::onKillFocus()
{
	InputSystem::get()->removeListner(this);
}

void CameraManager::registerCamera(Camera* cam)
{
	camList.push_back(cam);
}

void CameraManager::ChangeCam()
{
	currentCam++;
	ChangeCam(currentCam);
}

void CameraManager::ChangeCam(int index)
{
	for (int i = 0; i < camList.size(); i++)
		camList[i]->setActive(false);

	if (index >= camList.size())
		currentCam = index % camList.size();
	else
		currentCam = index;

	camList[currentCam]->setActive(true);

	std::cout << "Current Cam selected " << currentCam << std::endl;
}
