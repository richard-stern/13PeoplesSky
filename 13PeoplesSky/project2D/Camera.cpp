#include "Camera.h"
#include <iostream>

Camera* Camera::m_instance = nullptr;

Camera::Camera()
{
	m_fShakeDuration = 0.0f;
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
	m_CameraPosition.x = x - (m_Resolution.x * 0.5f);
	m_CameraPosition.y = y - (m_Resolution.y * 0.5f);

	UpdateShake(0.017f);
}

void Camera::SetPosition(Vector2 position)
{
	m_CameraPosition = position - (m_Resolution * 0.5f);
}

void Camera::UpdateShake(float deltatime) 
{
	if (m_fShakeDuration > 0.0f)
	{
		// Create random unit vector.
		Vector2 v2CamShakeOffset
		(
			-1.0f + (static_cast<float>(rand() % 101) / 50.0f),
			-1.0f + (static_cast<float>(rand() % 101) / 50.0f)
		);

		// Add unit vector to camera position multiplied by a magnitude.
		m_CameraPosition += v2CamShakeOffset * SHAKE_MAGNITUDE;

		// Count down shake duration.
		m_fShakeDuration -= deltatime;
	}
}

void Camera::AddShakeDuration(float duration) 
{
	m_fShakeDuration += duration;
}

void Camera::SetShakeDuration(float duration) 
{
	m_fShakeDuration = duration;
}

Vector2 Camera::GetPosition()
{
	return m_CameraPosition;
}

void Camera::SetResolution(Vector2 resolution)
{
	m_Resolution = resolution;
}

Vector2 Camera::GetResolution()
{
	return m_Resolution;
}

void Camera::Destroy()
{
	delete m_instance;
}

