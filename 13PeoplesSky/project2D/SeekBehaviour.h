#pragma once
#include "BaseBehaviour.h"

class SeekBehaviour : public BaseBehaviour
{
public:
	SeekBehaviour();
	~SeekBehaviour();

	Vector2 update(Actor* pPlayer, Enemy* pEnemy);
};

