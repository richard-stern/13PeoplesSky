#include "Rock.h"
#include "TextureManager.h"
#include "CollisionManager.h"

Rock::Rock()
{
	//set health and max health to a random value between 2 and 4
	this->SetMaxHealth((rand() % 3) + 1);
	this->SetHealth = this->GetMaxHealth();

	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();

	//set texture to rock texture
	//TEMP TEXTURE, replace when new texture made
	this->SetTexture(textureMan->LoadTexture("./textures/rock_large.png"));

	//Sets random velocity, change numbers as neccesary
	m_v2Velocity = Vector2(rand() % 360, rand() % 360);

	//set collision layer so other objects can correctly detect that this collider is a rock
	this->GetCollider()->SetLayer(ECOLLISIONLAYER_ROCK);
}

Rock::~Rock()
{
}

void Rock::OnCollision(Actor* collidingObject, CollisionData* data)
{
	switch (collidingObject->GetCollider()->m_eLayer)
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;
	case(ECOLLISIONLAYER_PLAYER):
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity * 1 /*replace with collider normal*/) * 1/*replace with collider normal*/));
		break;
	case(ECOLLISIONLAYER_BULLET):
		this->ModifyHealth(-1);
		if (this->GetHealth() <= 0)
			this->SetVisible(false);
		break;
	case(ECOLLISIONLAYER_ROCK):
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity * 1 /*replace with collider normal*/) * 1/*replace with collider normal*/));
		break;
	case(ECOLLISIONLAYER_ENEMY):
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity * 1 /*replace with collider normal*/) * 1/*replace with collider normal*/));
		break;
	case(ECOLLISIONLAYER_HEALTH):
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity * 1 /*replace with collider normal*/) * 1/*replace with collider normal*/));
		break;
	}
}
