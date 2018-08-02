#include "Enemy.h"
#include "Player.h"
#include "Rock.h"
#include "Bullet.h"
#include "TextureManager.h"
#include "PursueBehaviour.h"
#include "AvoidBehaviour.h"
#include "ColliderManager.h"
#include "Primitives.h"
#include "GUI.h"


Enemy::Enemy()
{
	//i'm loading me mum's car, broom broom
	TextureManager* TextureManager = TextureManager::GetInstance();
	SetTexture(TextureManager->LoadTexture("./textures/car.png"));

	//*slaps top of enemy* this bad boy can take so many bullets
	SetHealth(3);

	//Creating the instances of the enemy's 2 behaviour types
	m_pursue = new PursueBehaviour;
	m_avoid = new AvoidBehaviour;

	PrimRectangle* collider = new PrimRectangle(36, 42);
	collider->SetLayer(ECOLLISIONLAYER_ENEMY);
	SetCollider(collider);

	//Making sure the enemy is actually drawn to start with
	SetVisible(true);
	
}

Enemy::~Enemy()
{
	//Spring cleaning
	delete m_pursue;
	delete m_avoid;
}

void Enemy::Update(Player* pPlayer, Rock* pRock)
{
	//Updates the distance between this class and the player every frame
	m_distToPlayer = pPlayer->GetPosition().dot(GetPosition());
	m_distToRock = pRock->GetPosition().dot(GetPosition());

	//When a destroyed enemy is far enough away from the player, redraw it
	if (m_distToPlayer > 800.0f && GetVisible() == false)
	{
		SetVisible(true);
	}

	//If player is within a certain radius, pursue player. Only pursues if the player is drawn
	if (m_distToPlayer < 600.0f && GetVisible() == true)
	{
		//first paramter is the object being sought, 2nd parameter is the pursuer
		// Whilst it's pursuing the player, we want the enemy to try and avoid all of the rocks
		m_pursue->update(pPlayer, this);
		if(m_distToRock < 200.f)
		m_avoid->update(pRock, this);
	}

	//If the enemy has been destroyed, it will flee the player so that it can reach a distance where it can "respawn"
	else if (GetVisible() == false)
	{
		m_avoid->update(pPlayer, this);
	}
}

//When the enemy collides with another object, rather than being "destroyed", it simply becomes invisible and runs away
void Enemy::OnCollision(Actor* collidingObject, CollisionData* data)
{
		switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//When the enemy hits a player, the enemy gets destroyed and the player takes 1 point of damage
		SetVisible(false);
		collidingObject->ModifyHealth(-1);
		break;
	case(ECOLLISIONLAYER_BULLET):
		//take damage from the bullet, bullet should also be destroyed on impact
		ModifyHealth(-1);
		if (GetHealth() <= 0)
		{
			SetVisible(false);
			GUI::GetInstance()->AddScore(5);
		}
		break;
	case(ECOLLISIONLAYER_ROCK):
		//formula for bouncing off of other rocks
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	case(ECOLLISIONLAYER_ENEMY):
		//formula for bouncing off of enemies
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	case(ECOLLISIONLAYER_HEALTH):
		//We don't want the enemy to interact with the health pickups at all, so we ignore them
		break;
	}
}

//Simple setter and getter for the object's speed variable
void Enemy::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

float Enemy::GetMaxSpeed()
{
	return m_maxSpeed;
}