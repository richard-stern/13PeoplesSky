#pragma once
#include "Enemy.h"


class Actor;
struct Vector2;

class BaseBehaviour
{
public:
	BaseBehaviour();
	virtual ~BaseBehaviour();

	virtual Vector2 update(Actor* pActor, float deltatime) = 0;

	Vector2 GetHeading();

	float m_weighting;
};

