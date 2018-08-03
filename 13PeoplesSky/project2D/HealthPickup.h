#pragma once
#include "Actor.h"

struct CollisionData;

class HealthPickup : public Actor
{
public:
	//------------------------------------
	//Constructor
	//Should do the following:
	//Request a texture from the texture manager. 
	//Set a random velocity. 
	//------------------------------------
	HealthPickup();

	//------------------------------------
	//Destructor
	//Should do the following:
	//Delete any pointers, don't delete texture. 
	//------------------------------------
	~HealthPickup();

	//------------------------------------
	// Updates position, velocity, etc
	// If the pickup has collided with the player or bullet the pickup will be destroyed
	//------------------------------------
	void Update(float deltaTime);

	//------------------------------------
	//OnCollision
	//Should do the following:
	//Detect whether the collision was caused by the player, a bullet, a rock, an enemy, or another health pickup. 
	//If the player or a bullet collides with the health pickup, the pickup should be destroyed. 
	//If anything else collides, it should bounce off harmlessly. 
	//------------------------------------
	void OnCollision(Actor* collidingObject, CollisionData* data);

private:
	bool m_collided;
};

