#pragma once
#include "GameObject.h"
#include "Matrix3.h"

class Collider;
struct CollisionData;

class Actor : public GameObject
{
private:
	Collider *m_pCollider; /* actor collider */

	/* health variables */
	int m_nHealth; /* current */
	int m_nMaxHealth; /* max */

	/* flag which indicates whether the actor has experienced a collision */
	bool m_bCollidedThisFrame;

protected:
	/* physics variables */
	Vector2 m_v2Velocity;
	float m_fAngularVelocity;
	float m_fDrag;
	float m_fMass;

public:
	Actor(); /* default constructor */
	Actor(Matrix3 m_m3StartPosition); /* argument constructor */
	virtual ~Actor(); /* destructor */

	virtual void Update(float deltaTime); /* virtual update function */
	void Draw(aie::Renderer2D *renderer);
	virtual void OnCollision(Actor *collidingObject, CollisionData *data) = 0; /* pure virtual OnCollision function */

	/* collider get/set */
	Collider* GetCollider();
	void SetCollider(Collider *collider);

	/* health get/set */
	int GetHealth();
	void SetHealth(int health);
	int GetMaxHealth();
	void SetMaxHealth(int maxHealth);
	void ModifyHealth(int value);

	/* physics get/set */
	Vector2 GetVelocity();
	void SetVelocity(Vector2 velocity);
	float GetAngularVelocity();
	void SetAngularVelocity(float angularVelocity);
	float GetDrag();
	void SetDrag(float drag);
	float GetMass();
	void SetMass(float mass);

	/* collidedThisFrame get/set */
	bool GetCollidedThisFrame();
	void SetCollidedThisFrame(bool toggle);
	void WrapAndRespawn();
};

