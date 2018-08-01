#pragma once
#include "Actor.h"
#include "Collider.h"

class Bullet : public Actor
{
public:
	Bullet();
	~Bullet();

	void Update(float deltaTime);

	//-----------------
	// Fire a bullet
	// Params: initial position
	//			initial velocity
	//-----------------
	void Shoot(Vector2 position, Vector2 velocity);

	//-----------------
	// Destroys the bullet on collision
	//-----------------
	void OnCollision(GameObject* collidingObject);

private:
	Collider* m_pCollider;
};

