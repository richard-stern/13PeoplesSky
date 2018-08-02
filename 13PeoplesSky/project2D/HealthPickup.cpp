#include "HealthPickup.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Primitives.h"

HealthPickup::HealthPickup()
{
	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();
	CollisionManager* collisionMan = CollisionManager::GetInstance();

	//set texture to health texture
	//TEMP TEXTURE, replace when new texture made
	SetTexture(textureMan->LoadTexture("./textures/health.png"));

	//Sets random velocity, change numbers as neccesary
	SetVelocity(Vector2((float)(rand() % 360), (float)(rand() % 360)));

	//Creates a collider, sets neccesary variables. 
	PrimRectangle* collider = new PrimRectangle(64, 64);
	collider->SetLayer(ECOLLISIONLAYER_ROCK);
	SetCollider(collider);
	collisionMan->AddObject(this);
}

HealthPickup::~HealthPickup()
{
}

void HealthPickup::OnCollision(Actor* collidingObject, CollisionData* data)
{
	switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//destroy health pickup
		//player should also gain health, code done in player class
		this->SetVisible(false);
		break;
	case(ECOLLISIONLAYER_BULLET):
		//destroy health pickup
		//bullet should also be destroyed, code would be done in bullet class
		this->SetVisible(false);
		break;
	case(ECOLLISIONLAYER_ROCK):
		//formula for bouncing off of rocks
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	case(ECOLLISIONLAYER_ENEMY):
		//formula for bouncing off of enemies
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	case(ECOLLISIONLAYER_HEALTH):
		//formula for bouncing off of other health pickups
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	}
}
