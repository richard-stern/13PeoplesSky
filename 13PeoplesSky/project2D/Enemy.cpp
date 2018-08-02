#include "Enemy.h"
#include "Player.h"
#include "Rock.h"
#include "TextureManager.h"
#include "PursueBehaviour.h"
#include "AvoidBehaviour.h"


Enemy::Enemy()
{
	pTexture = pTexture->GetInstance();
	this->SetHealth(100);

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

	//If player is within a certain radius, pursue player
	if (m_distBetween < 200.0f)
	{
		m_pursue->update(pPlayer, this);
	}

	m_avoid->update(pRock, this);	
}

void Enemy::OnCollision(Actor* collidingObject, CollisionData* data)
{
	this->SetVisible(false);
}

float Enemy::GetMaxSpeed()
{
	return m_maxSpeed;
}
