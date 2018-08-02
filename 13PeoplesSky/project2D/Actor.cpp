#include "Actor.h"

Actor::Actor()
{
	m_nMaxHealth = 10;
	m_nHealth = m_nMaxHealth;
}

Actor::Actor(Matrix3 m_m3StartPosition)
{
	m_m3GlobalMatrix = m_m3StartPosition;
	m_nMaxHealth = 10;
	m_nHealth = m_nMaxHealth;
	m_bCollidedThisFrame = false;
}

Actor::~Actor()
{
}

/*
Function:	 Update
Input/s:	 float
Description: Calls base class (GameObject) Update function. Then updates attached
collider object (bounding boxes & other collision data)
*/
void Actor::Update(float deltaTime)
{
	/* make new translation & rotation matrices */
	Matrix3 translation, rotation;
	translation.SetPosition(m_m3LocalMatrix.GetPosition() + m_v2Velocity * deltaTime);
	rotation.SetRotate2D(m_fRotation + m_fAngularVelocity * deltaTime);

	m_m3LocalMatrix = rotation * translation; /* update local transform */

	GameObject::Update(deltaTime); /* call base object update */
	m_pCollider.UpdateBounds(&m_m3GlobalMatrix); /* update collision settings */
}

/*
Function:	 GetCollider
Output:		 Collider
Description: Retrieve actor's collider
*/
Collider Actor::GetCollider()
{
	return m_pCollider;
}

/*
Function:	 SetCollider
Input/s:	 Collider
Description: Set actor's collider
*/
void Actor::SetCollider(Collider collider)
{
	m_pCollider = collider;
}

/*
Function:	 GetHealth
Output:		 int
Description: Retrieve actor's health
*/
int Actor::GetHealth()
{
	return m_nHealth;
}

/*
Function:	 SetHealth
Input/s:	 int
Description: Set actor's health
*/
void Actor::SetHealth(int health)
{
	m_nHealth = health;
}

/*
Function:	 GetMaxHealth
Output:		 int
Description: Retrieve actor's max health
*/
int Actor::GetMaxHealth()
{
	return m_nMaxHealth;
}

/*
Function:	 SetMaxHealth
Input/s:	 int
Description: Set actor's health
*/
void Actor::SetMaxHealth(int maxHealth)
{
	m_nMaxHealth = maxHealth;
}

/*
Function:	 GetCollidedThisFrame
Output:		 bool
Description: Retrieve actor's collidedThisFrame flag
*/
bool Actor::GetCollidedThisFrame()
{
	return m_bCollidedThisFrame;
}

/*
Function:	 SetCollidedThisFrame
Input/s:	 bool
Description: Set actor's collidedThisFrame flag
*/
void Actor::SetCollidedThisFrame(bool toggle)
{
	m_bCollidedThisFrame = toggle;
}