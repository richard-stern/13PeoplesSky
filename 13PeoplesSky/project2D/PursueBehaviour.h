#pragma once
#include "BaseBehaviour.h"

class Actor;
class SeekBehaviour;

class PursueBehaviour : public BaseBehaviour
{
public:
	PursueBehaviour();
	~PursueBehaviour();

	Vector2 update(Actor* pTarget, Enemy* pPursuer);

	SeekBehaviour* m_seek;
};

