#pragma once
#include "Actor.h"

struct CollisionData;

class AmmoPickup : public Actor
{
public:
	AmmoPickup();
	~AmmoPickup();
	void Update(float deltaTime);
	void OnCollision(Actor* collidingObject, CollisionData* data);
private:
	bool m_collided;
};

