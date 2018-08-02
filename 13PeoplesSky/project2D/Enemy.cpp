#include "Enemy.h"
#include "Player.h"
#include "Rock.h"
#include "TextureManager.h"


Enemy::Enemy()
{
	pTexture = pTexture->GetInstance();
	this->SetHealth(100);
}

Enemy::~Enemy()
{

}

void Enemy::Update(Player* pPlayer)
{
	
}

void Enemy::OnCollision() 
{

}

float Enemy::GetMaxSpeed()
{
	return m_maxSpeed;
}
