#pragma once
#include "Matrix4x4.h"
#include "InputListener.h"
#include "AGameObject.h"

class AppWindow;

class Camera : public InputListener, public AGameObject
{
public:
	Camera(AppWindow* window, const Vector3D& position);
	//AGameObject::AGameObject(const Vector3D& position) : m_position(position) { }
	virtual void update() override;
	~Camera() {}

	//Inherited via InputListener
#if 1
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	//Mouse
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;

	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;
#endif

#if 0
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	//Mouse
	virtual void onMouseMove(const Point& mouse_pos);

	virtual void onLeftMouseDown(const Point& delta_mouse_pos);
	virtual void onLeftMouseUp(const Point& delta_mouse_pos);

	virtual void onRightMouseDown(const Point& delta_mouse_pos);
	virtual void onRightMouseUp(const Point& delta_mouse_pos);
#endif
	Matrix4x4 getViewMatrix();
	bool getCameraState();

private:
	Matrix4x4 viewMatrix;
	AppWindow* m_window = nullptr;
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	bool isPerspective = true;
	bool isHoldingC = false;
	
	float m_forward = 0.0f;
	float m_right = 0.0f;

	float m_delta_pos = 0;
	float m_delta_scale = 0;
	float m_delta_rot = 0;
	float m_scale_cube = 1.0f;
};

