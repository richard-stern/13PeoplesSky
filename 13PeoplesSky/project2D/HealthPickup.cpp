#include "HealthPickup.h"
#include "TextureManager.h"


HealthPickup::HealthPickup()
{
	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();

	//set texture to health texture
	//TEMP TEXTURE, replace when new texture made
	this->SetTexture(textureMan->LoadTexture("./textures/health.png"));

	//Sets random velocity, change numbers as neccesary
	this->SetVelocity(Vector2(rand() % 360, rand() % 360));

	//set collision layer so other objects can correctly detect that this collider is a rock
	this->m_pCollider.SetLayer(ECOLLISIONLAYER_HEALTH);
}


HealthPickup::~HealthPickup()
{
}

void HealthPickup::OnCollision(Actor* collide)
{
	switch (collide->m_pCollider.m_eLayer)
	{
	case(ECOLLISIONLAYER_NONE):
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//player should also gain health, code done in player class
		this->SetVisible = false;
		break;
	case(ECOLLISIONLAYER_BULLET):
		//bullet should also be destroyed
		this->SetVisible = false;
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
