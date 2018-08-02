#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Matrix3.h"

class Actor : public GameObject
{
private:
	Collider m_pCollider; /* actor collider */

	/* health variables */
	int m_nHealth; /* current */
	int m_nMaxHealth; /* max */

	/* physics variables */
	Vector2 m_v2Velocity;
	float m_fAngularVelocity;
	float m_fDrag;
	float m_fMass;

	/* flag which indicates whether the actor has experienced a collision */
	bool m_bCollidedThisFrame;

public:
	Actor(); /* default constructor */
	Actor(Matrix3 m_m3StartPosition); /* argument constructor */
	virtual ~Actor(); /* destructor */

	virtual void Update(float deltaTime); /* virtual update function */
	virtual void OnCollision(Actor *collidingObject) = 0; /* pure virtual OnCollision function */

	/* collider get/set */
	Collider GetCollider();
	void SetCollider(Collider collider);

	/* health get/set */
	int GetHealth();
	void SetHealth(int health);
	int GetMaxHealth();
	void SetMaxHealth(int maxHealth);

	/* collidedThisFrame get/set */
	bool GetCollidedThisFrame();
	void SetCollidedThisFrame(bool toggle);
};

