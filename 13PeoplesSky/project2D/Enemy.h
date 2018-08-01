#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	float GetMaxSpeed();

private:
	float m_maxSpeed = 300.0f;
};

