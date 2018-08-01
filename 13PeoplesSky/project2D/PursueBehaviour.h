#pragma once
#include "BaseBehaviour.h"

class Actor;
class SeekBehaviour;

class PursueBehaviour : public BaseBehaviour
{
public:
	PursueBehaviour();
	~PursueBehaviour();

	Vector2 update(Actor* pPlayer, Enemy* pEnemy);

	SeekBehaviour* m_seek;
};

