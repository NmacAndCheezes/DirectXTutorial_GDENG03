#pragma once
#include <vector>
#include "Point.h"
#include "InputListener.h"

class Camera;
class CameraManager : public InputListener
{
public:
	CameraManager();
	CameraManager(int initialCam);
	~CameraManager();
public:
	//Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	//Mouse
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;

	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

	void onFocus();
	void onKillFocus();

public:
	void registerCamera(Camera* cam);
	void ChangeCam();
	void ChangeCam(int index);
private:
	std::vector<Camera*> camList;
	int currentCam = 0;
	bool isHoldingC = false;
};

