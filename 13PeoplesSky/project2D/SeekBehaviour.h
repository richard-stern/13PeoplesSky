#pragma once
#include "BaseBehaviour.h"

class SeekBehaviour : public BaseBehaviour
{
public:
	SeekBehaviour();
	~SeekBehaviour();

	Vector2 update(Actor* pTarget, Enemy* pSeeker);
	Vector2 update(Vector2 targetPos, Enemy* pSeeker);
};

