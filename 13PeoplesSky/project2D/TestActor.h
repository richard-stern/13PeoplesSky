#pragma once
#include "Actor.h"
#include "CollisionManager.h"

class TestActor : public Actor
{
public:

	TestActor();

	~TestActor();

	void OnCollision(Actor* collidingObject, CollisionData* data) override;
};

