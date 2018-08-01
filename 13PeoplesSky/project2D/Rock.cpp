#include "Rock.h"
#include "TextureManager.h"


Rock::Rock()
{
	//set health and max health to a random value between 2 and 4
	m_nMaxHealth = (rand() % 3) + 1;
	m_nHealth = m_nMaxHealth;

	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();

	//set texture to rock texture
	//TEMP TEXTURE, replace when new texture made
	this->SetTexture(textureMan->LoadTexture("./textures/rock_large.png"));

	//Sets random velocity, change numbers as neccesary
	this->SetVelocity(Vector2(rand() % 360, rand() % 360));

	//set collision layer so other objects can correctly detect that this collider is a rock
	this->m_pCollider.SetLayer(ECOLLISIONLAYER_ROCK);
}

Rock::~Rock()
{
}

void Rock::OnCollision(Actor* collide)
{
	switch (collide->m_pCollider.m_eLayer)
	{
	case(ECOLLISIONLAYER_NONE):
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//bounce off
		break;
	case(ECOLLISIONLAYER_BULLET):
		m_nHealth -= 1;
		if (m_nHealth <= 0)
			this->SetVisible(false);
		break;
	case(ECOLLISIONLAYER_ROCK):
		//bounce off
		break;
	case(ECOLLISIONLAYER_ENEMY):
		//bounce off
		break;
	case(ECOLLISIONLAYER_HEALTH):
		//bounce off
		break;
	}
}
