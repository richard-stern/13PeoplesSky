#pragma once
#include "GameObject.h"
//#include "Collider.h"
#include "Matrix3.h"

class Actor : public GameObject
{
public:
	//Collider m_pCollider;

	/* health variables */
	int m_nHealth; /* current */
	int m_nMaxHealth; /* max */

	Actor(); /* default constructor */
	Actor(Matrix3 m_m3StartPosition); /* argument constructor */
	virtual ~Actor(); /* destructor */

	virtual void Update(float deltaTime) = 0; /* pure virtual update function */
	virtual void OnCollision(GameObject *collidingObject) = 0; /* pure virtual OnCollision function */
};

