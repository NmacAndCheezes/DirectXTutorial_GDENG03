#include "Camera.h"
#include "GraphicsEngine.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "AppWindow.h"
#include <iostream>

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj; //projection matrix
	unsigned int m_time = 0;
};

Camera::Camera(AppWindow* window, const Vector3D& position) : m_window(window), AGameObject(position)
{
	viewMatrix.setTranslation(m_position);
}

void Camera::update()
{
	AGameObject::update();

	constant cc;

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	if (isPerspective)
	{
		Matrix4x4 temp;

		temp.setIdentity();
		temp.setRotationX(m_rot_x);
		world_cam *= temp;

		temp.setIdentity();
		temp.setRotationY(m_rot_y);
		world_cam *= temp;

		Vector3D new_pos = viewMatrix.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);

		new_pos = new_pos + world_cam.getXDirection() * (m_right * 0.3f);
		world_cam.setTranslation(new_pos);
	}
	else
	{
		// pan camera depending on key presses
		Vector3D new_pos = viewMatrix.getTranslation() + Vector3D(0, m_forward * 0.3f, 0);
		new_pos = new_pos + Vector3D(m_right * 0.3f, 0, 0);
		world_cam.setTranslation(new_pos);
	}

	world_cam.inverse();
	this->viewMatrix = world_cam;
}

void Camera::onKeyDown(int key)
{
	const float speed = 3.714;
	if (key == 'W')
	{
		//m_rot_x += speed * EngineTime::get()->getDT();
		std::cout << "pressed W" << std::endl;
		m_forward = 1.0f; //front back
	}
	else if (key == 'S')
	{
		//m_rot_x -= speed * EngineTime::get()->getDT();
		std::cout << "pressed S" << std::endl;
		m_forward = -1.0f; //front back
	}

	if (key == 'A')
	{
		//m_rot_y += speed * EngineTime::get()->getDT();
		std::cout << "pressed A" << std::endl;
		m_right = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= speed * EngineTime::get()->getDT();
		std::cout << "pressed D" << std::endl;
		m_right = 1.0f;
	}

	//std::cout << m_right << ", " << m_forward << std::endl;
}

void Camera::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	int width = m_window->getClientWindowRect().right - m_window->getClientWindowRect().left;
	int height = m_window->getClientWindowRect().bottom - m_window->getClientWindowRect().top;

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void Camera::onLeftMouseDown(const Point& delta_mouse_pos)
{
	std::cout << "Left Mouse Down\n";
	m_scale_cube = 0.5f;
}

void Camera::onLeftMouseUp(const Point& delta_mouse_pos)
{
	std::cout << "Left Mouse Up\n";
	m_scale_cube = 1.0f;
}

void Camera::onRightMouseDown(const Point& delta_mouse_pos)
{
	std::cout << "Right Mouse Down\n";
	m_scale_cube = 2.0f;
}

void Camera::onRightMouseUp(const Point& delta_mouse_pos)
{
	std::cout << "Right Mouse Up\n";
	m_scale_cube = 1.0f;
}

Matrix4x4 Camera::getViewMatrix()
{
	return viewMatrix;
}

bool Camera::getCameraState()
{
	return isPerspective;
}


