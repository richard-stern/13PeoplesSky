#pragma once
#include "Actor.h"

struct CollisionData;

class Bullet : public Actor
{
public:
	Bullet();

	void Update(float deltaTime);

	//-----------------
	// Fire a bullet
	// Params: initial position
	//			initial velocity
	//-----------------
	void Shoot(Vector2 position, Vector2 velocity, Vector2 playerVelocity);

	//-----------------
	// Destroys the bullet on collision
	//-----------------
	void OnCollision(Actor* collidingObject, CollisionData* _collision_data);

private:
	bool m_collided;
};

