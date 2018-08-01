#pragma once
#include "BaseBehaviour.h"

class Enemy;
class Actor;

class FleeBehaviour : public BaseBehaviour
{
public:
	FleeBehaviour();
	~FleeBehaviour();

	Vector2 update(Actor* pPlayer, Enemy* pEnemy);
};