#pragma once
#include "Enemy.h"


class Actor;
struct Vector2;

class BaseBehaviour
{
public:
	BaseBehaviour();
	virtual ~BaseBehaviour();

	virtual Vector2 update(Actor* pActor, Enemy* pEnemy) = 0;

	float m_weighting;
};