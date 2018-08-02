#pragma once
#include "Actor.h"
#include "CollisionManager.h"

class TestActor2 : public Actor
{
public:

	TestActor2();

	~TestActor2();

	void Update(float deltaTime) override;

	void OnCollision(Actor* collidingObject, CollisionData* data) override;
};

