#pragma once
#include "Vector2.h"

#define SHAKE_MAGNITUDE 5.0f

class Camera
{
protected:
	Camera(void);
	~Camera(void);
	static Camera* m_instance;
	Vector2 m_CameraPosition;
	Vector2 m_Resolution;
	float m_fShakeDuration;
public:
	static Camera* GetInstance();
	static void Destroy();
	void SetPosition(float x, float y);
	void SetPosition(Vector2 position);
	void Update(float deltatime);
	void AddShakeDuration(float duration);
	void SetShakeDuration(float duration);
	void SetResolution(Vector2 resolution);
	Vector2 GetResolution();
	Vector2 GetPosition();
};

