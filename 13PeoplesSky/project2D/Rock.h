#pragma once
#include "Actor.h"

struct CollisionData;
class SmallRock;

class Rock : public Actor
{
private:
	SmallRock* m_pSmallRock1;
	SmallRock* m_pSmallRock2;

public:
	//------------------------------------
	//Constructor
	//Should do the following:
	//Request a texture from texture manager. 
	//Set a random velocity. 
	//Set max and current health to three (3). 
	//------------------------------------
	Rock();

	//------------------------------------
	//Destructor
	//Should do the following:
	//Delete any pointers, don't delete texture. 
	//------------------------------------
	~Rock();

	//------------------------------------
	//OnCollision
	//Should do the following:
	//Detect whether the collision was caused by a bullet, the player, a health pickup, or another rock. 
	//If collision was caused by anything other than a bullet, the rock should bounce off without taking damage. 
	//If a bullet collided, the rock should take one (1) damage. 
	//If the rock's health is reduced to zero (0), the m_bVisible variable should be set to 'false'.
	//------------------------------------
	void OnCollision(Actor* collidingObject, CollisionData* data);

	bool WrapAndRespawn();

	void Update(float deltaTime);

private:
	bool m_destroyed;
};

