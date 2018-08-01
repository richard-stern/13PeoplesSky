#include "Camera.h"

Camera* Camera::m_instance = nullptr;

Camera::Camera()
{


}

Camera::~Camera()
{


}

Camera* Camera::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Camera;
	}
	return m_instance;
}

void Camera::SetPosition(float x, float y)
{
	m_CameraPosition.x = x;
	m_CameraPosition.y = y;
}

void Camera::SetPosition(Vector2 position)
{
	m_CameraPosition = position;
}

Vector2 Camera::GetPosition()
{
	return m_CameraPosition;
}

void Camera::Destroy()
{
	delete m_instance;
}