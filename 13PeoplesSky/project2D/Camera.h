#pragma once
#include "Vector2.h"

class Camera
{
protected:
	Camera(void);
	~Camera(void);
	static Camera* m_instance;
	Vector2 m_CameraPosition;
public:
	static Camera* GetInstance();
	static void Destroy();
	void SetPosition(float x, float y);
	void SetPosition(Vector2 position);
	Vector2 GetPosition();
};

