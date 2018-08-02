#include "Actor.h"
#include "Primitives.h"
#include "CollisionManager.h"

Actor::Actor()
{
	m_nMaxHealth = 10;
	m_nHealth = m_nMaxHealth;
	m_bCollidedThisFrame = false;
	m_pCollider = nullptr;

	m_fAngularVelocity = 0.0f;
	m_fDrag = 0.0f;
}

Actor::Actor(Matrix3 m_m3StartPosition)
{
	m_m3GlobalMatrix = m_m3StartPosition;
	m_nMaxHealth = 10;
	m_nHealth = m_nMaxHealth;
	m_bCollidedThisFrame = false;
	m_pCollider = nullptr;

	m_fAngularVelocity = 0.0f;
	m_fDrag = 0.0f;
}

Actor::~Actor()
{
	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}
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
	SetPosition(GetPosition() + m_v2Velocity * deltaTime);
	SetRotation(GetRotation() + m_fAngularVelocity * deltaTime);

	GameObject::Update(deltaTime); /* call base object update */
	
	if (m_pCollider)
	{
		m_pCollider->UpdateBounds(&m_m3GlobalMatrix); /* update collision settings */
	}
}

void Actor::Draw(aie::Renderer2D *renderer)
{
	GameObject::Draw(renderer); /* call base class draw */

	if (m_pCollider)
		m_pCollider->DrawCollider(m_v2Position, renderer); /* draws bounding box */
}

/*
Function:	 GetCollider
Output:		 Collider
Description: Retrieve actor's collider
*/
Collider* Actor::GetCollider()
{
	return m_pCollider;
}

/*
Function:	 SetCollider
Input/s:	 Collider
Description: Set actor's collider
*/
void Actor::SetCollider(Collider *collider)
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
Function:	 ModifyHealth
Input/s:	 int
Description: Takes in either a positive/negative integer value, and increments/decrements
accordingly
*/
void Actor::ModifyHealth(int value)
{
	m_nHealth += value;
}

/*
Function:	 GetVelocity
Output:		 Vector2
Description: Retrieves actor's velocity
*/
Vector2 Actor::GetVelocity()
{
	return m_v2Velocity;
}

/*
Function:	 SetVelocity
Input/s:	 Vector2
Description: Set actor's velocity
*/
void Actor::SetVelocity(Vector2 velocity)
{
	m_v2Velocity = velocity;
}

/*
Function:	 GetAngularVelocity
Output:		 float
Description: Retrieves actor's angular velocity
*/
float Actor::GetAngularVelocity()
{
	return m_fAngularVelocity;
}

/*
Function:	 SetAngularVelocity
Input/s:	 float
Description: Sets actor's angular velocity
*/
void Actor::SetAngularVelocity(float angularVelocity)
{
	m_fAngularVelocity = angularVelocity;
}

/*
Function:	 GetDrag
Output:		 float
Description: Retrieves actor's drag
*/
float Actor::GetDrag()
{
	return m_fDrag;
}

/*
Function:	 SetDrag
Input/s:	 float
Description: Sets actor's angular velocity
*/
void Actor::SetDrag(float drag)
{
	m_fDrag = drag;
}

/*
Function:	 GetMass
Output:		 float
Description: Retrieves actor's mass
*/
float Actor::GetMass()
{
	return m_fMass;
}

/*
Function:	 SetMass
Input/s:	 float
Description: Sets actor's mass
*/
void Actor::SetMass(float mass)
{
	m_fMass = mass;
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