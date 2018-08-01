#include "Actor.h"

Actor::Actor()
{
	m_nMaxHealth = 100;
	m_nHealth = m_nMaxHealth;
}

Actor::Actor(Matrix3 m_m3StartPosition)
{
	m_m3GlobalMatrix = m_m3StartPosition;
	m_nMaxHealth = 100;
	m_nHealth = m_nMaxHealth;
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
	GameObject::Update(deltaTime);
	m_pCollider.UpdateBounds(&m_m3GlobalMatrix);
}