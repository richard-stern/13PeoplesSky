#include "Rock.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Primitives.h"

Rock::Rock()
{
	//set health and max health to a random value between 2 and 4
	SetMaxHealth((rand() % 3) + 1);
	SetHealth(GetMaxHealth());

	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();
	CollisionManager* collisionMan = CollisionManager::GetInstance();

	//set texture to rock texture
	//TEMP TEXTURE, replace when new texture made
	SetTexture(textureMan->LoadTexture("./textures/rock_large.png"));

	//Sets random velocity, change numbers as neccesary
	SetVelocity(Vector2((float)(rand() % 360), (float)(rand() % 360)));

	//Creates a collider, sets neccesary variables. 
	PrimRectangle* collider = new PrimRectangle(64, 64);
	collider->SetLayer(ECOLLISIONLAYER_ROCK);
	SetCollider(collider);
	collisionMan->AddObject(this);

}

Rock::~Rock()
{
}

void Rock::OnCollision(Actor* collidingObject, CollisionData* data)
{
	switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//formula for bouncing off of player
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	case(ECOLLISIONLAYER_BULLET):
		//take damage from the bullet, bullet should also be destroyed on impact
		ModifyHealth(-1);
		if (GetHealth() <= 0)
			SetVisible(false);
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
		//formula for bouncing off of health pickups
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;
	}
}
