#pragma once
#include "Actor.h"
class SmallRock :
	public Actor
{
public:
	//------------------------------------
	//Constructor
	//Should do the following:
	//Request a texture from texture manager. 
	//Set a random velocity. 
	//Set max and current health to three (3). 
	//------------------------------------
	SmallRock();

	//------------------------------------
	//Destructor
	//Should do the following:
	//Delete any pointers, don't delete texture. 
	//------------------------------------
	~SmallRock();

	//------------------------------------
	//OnCollision
	//Should do the following:
	//Detect whether the collision was caused by a bullet, the player, a health pickup, or another rock. 
	//If collision was caused by anything other than a bullet, the rock should bounce off without taking damage. 
	//If a bullet collided, the rock should take one (1) damage. 
	//If the rock's health is reduced to zero (0), the m_bVisible variable should be set to 'false'.
	//------------------------------------
	void OnCollision(Actor* collidingObject, CollisionData* data);

	void SpawnSelf(Vector2 position);

	bool WrapAndRespawn();

	void Update(float deltatime);
	void Draw(aie::Renderer2D *renderer);

private:
	bool m_destroyed;
};

