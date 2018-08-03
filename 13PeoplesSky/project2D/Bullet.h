#pragma once
#include "Actor.h"

struct CollisionData;
enum ELayer;

class Bullet : public Actor
{
public:
	Bullet(ELayer layer, ELayer ignoreLayer);

	void Update(float deltaTime);

	//-----------------
	// Fire a bullet relative to the player's velocity
	// Params: initial position
	//			initial velocity
	//			Player velocity
	//-----------------
	void Shoot(Vector2 position, Vector2 velocity, Vector2 ownerVelocity);

	//-----------------
	// Destroys the bullet on collision
	//-----------------
	void OnCollision(Actor* collidingObject, CollisionData* _collision_data);

private:
	bool m_collided;
};

