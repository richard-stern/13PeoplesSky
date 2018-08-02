#pragma once
#include "BaseBehaviour.h"

class Enemy;
class Actor;

class FleeBehaviour : public BaseBehaviour
{
public:
	FleeBehaviour();
	~FleeBehaviour();

	Vector2 update(Actor* pTarget, Enemy* pFleeing);
	Vector2 update(Vector2 targetPos, Enemy* pFleeing);
};