#pragma once
#include "BaseBehaviour.h"

class Actor;
class FleeBehaviour;

class AvoidBehaviour : public BaseBehaviour
{
public:
	AvoidBehaviour();
	~AvoidBehaviour();

	Vector2 update(Actor* pTarget, Enemy* pAvoider);

	FleeBehaviour* m_flee;
};

