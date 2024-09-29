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

Camera::Camera(AppWindow* window, std::string name) : AGameObject(name), m_window(window)
{
	InputSystem::get()->addListner(this);
	//updateViewMatrix();

	//m_world_cam.setTranslation(Vector3D(0, 0, -2));
}

void Camera::update()
{
	AGameObject::update();

	//camera_view_matrix.printMatrix();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.X());
	worldCam *= temp;

	temp.setRotationY(localRot.Y());
	worldCam *= temp;

	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	/*Vector3D cameraPos = this->worldCameraMatrix.getTranslation() + (worldCam.getZDirection() * (this->forwardDirection * 0.01f));
	std::cout << "Camera pos: " << cameraPos.getX() << " " << cameraPos.getY() << " " << cameraPos.getZ() << "\n";
	temp.setTranslation(cameraPos);
	worldCam = worldCam.multiplyTo(temp);
	this->worldCameraMatrix = worldCam;*/

	worldCam.inverse();
	this->camera_view_matrix = worldCam;
#if 0
	constant cc;
	cc.m_time = ::GetTickCount64();

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();

	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	//Vector3D new_pos = camera_view_matrix.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);

	//new_pos = new_pos + world_cam.getXDirection() * (m_right * 0.3f);
	temp.setTranslation(m_local_position);
	world_cam *= temp;

	world_cam.inverse();

	//cc.m_view = world_cam;
	camera_view_matrix = world_cam;

	/*
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);
	*/

	//float width = m_window->getWidth();
	//float height = m_window->getHeight();
	//cc.m_proj.setPerspectiveForLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	//m_window->getConstantBuffer()->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_window->getVertexShader(), m_window->getConstantBuffer());
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_window->getPixelShader(), m_window->getConstantBuffer());
#endif
}

void Camera::release()
{
	AGameObject::release();
	//InputSystem::get()->removeListner(this);
}

void Camera::onKeyDown(int key)
{
	const float speed = 3.714;
	float x = m_local_position.X();
	float y = m_local_position.Y();
	float z = m_local_position.Z();

	if (key == 'W')
	{
		//m_rot_x += speed * EngineTime::get()->getDT();
		//m_forward = 1.0f; //front back
		z += EngineTime::get()->getDT() * speed;
		m_local_position.setVector3D(x, y, z);
		updateViewMatrix();
	}
	else if (key == 'S')
	{
		//m_rot_x -= speed * EngineTime::get()->getDT();
		//m_forward = -1.0f; //front back
		z -= EngineTime::get()->getDT() * speed;
		m_local_position.setVector3D(x, y, z);
		updateViewMatrix();
	}

	if (key == 'A')
	{
		//m_rot_y += speed * EngineTime::get()->getDT();
		//m_right = -1.0f;
		x += EngineTime::get()->getDT() * speed;
		m_local_position.setVector3D(x, y, z);
		updateViewMatrix();
	}
	else if (key == 'D')
	{
		//m_rot_y -= speed * EngineTime::get()->getDT();
		//m_right = 1.0f;
		x -= EngineTime::get()->getDT() * speed;
		m_local_position.setVector3D(x, y, z);
		updateViewMatrix();
	}

	//std::cout << this->m_local_position.X() << ", " << this->m_local_position.Y() << ", " << this->m_local_position.Z() << std::endl;
}

void Camera::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	int width = (m_window->getClientWindowRect().right - m_window->getClientWindowRect().left);
	int height = (m_window->getClientWindowRect().bottom - m_window->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::get()->getDT() * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::get()->getDT() * 0.1f;

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

void Camera::onFocus()
{
	InputSystem::get()->addListner(this);
}

void Camera::onKillFocus()
{
	InputSystem::get()->removeListner(this);
}

Matrix4x4 Camera::getCameraViewMatrix()
{
	return camera_view_matrix;
}

float Camera::getAspectRatio()
{
	int width = (m_window->getClientWindowRect().right - m_window->getClientWindowRect().left);
	int height = (m_window->getClientWindowRect().bottom - m_window->getClientWindowRect().top);
	return (float)width / (float)height;
}


