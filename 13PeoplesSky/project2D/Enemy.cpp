#include "Enemy.h"
#include "Player.h"
#include "Rock.h"
#include "Bullet.h
#include "TextureManager.h"
#include "PursueBehaviour.h"
#include "AvoidBehaviour.h"


Enemy::Enemy()
{
	pTexture = pTexture->GetInstance();
	this->SetHealth(3);

	m_pursue = new PursueBehaviour;
	m_avoid = new AvoidBehaviour;
}

Enemy::~Enemy()
{
	delete m_pursue;
	delete m_avoid;
}

void Enemy::Update(Player* pPlayer, Rock* pRock)
{
	//Updates the distance between this class and the player every frame
	m_distBetween = pPlayer->GetPosition().dot(this->GetPosition());

	//When a destroyed enemy is far enough away from the player, redraw it
	if (m_distBetween > 800.0f && this->GetVisible() == false)
	{
		this->SetVisible(true);
	}

	//If player is within a certain radius, pursue player. Only pursues if the player is drawn
	if (m_distBetween < 600.0f && this->GetVisible() == true)
	{
		m_pursue->update(pPlayer, this);
	}

	//If the enemy has been destroyed, it will flee the player so that it can reach a distance where it can "respawn"
	else if (m_distBetween > 5.0f && this->GetVisible() == false)
	{
		m_avoid->update(pPlayer, this);
	}

	m_avoid->update(pRock, this);	
}

//When the enemy collides with another object, rather than being "destroyed", it simply becomes invisible and runs away
void Enemy::OnCollision(Actor* collidingObject, CollisionData* data)
{
	this->SetVisible(false);

	//When the enemy collides with an object (being rocks, or the player) "destroy" the enemy and deal 1 damage to the object.
	collidingObject->ModifyHealth(-1);
}

float Enemy::GetMaxSpeed()
{
	return m_maxSpeed;
}
