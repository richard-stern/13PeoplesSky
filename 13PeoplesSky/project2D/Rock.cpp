#include "Rock.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Primitives.h"

Rock::Rock()
{
	//set health and max health to a random value between 2 and 4
	SetMaxHealth((rand() % 3) + 2);
	SetHealth(GetMaxHealth());

	//set self to visible
	SetVisible(true);

	//set wrap to true
	m_bWrapAndRespawn = true;

	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();
	CollisionManager* collisionMan = CollisionManager::GetInstance();

	//set texture to rock texture
	//TEMP TEXTURE, replace when new texture made
	SetTexture(textureMan->LoadTexture("./textures/rock_large.png"));

	//Sets random velocity, change numbers as neccesary
	SetVelocity(Vector2((float)((rand() % 50) - 25), (float)((rand() % 30) - 50)));

	//Sets random rotation in radians
	SetRotation(((float)(rand() % 32) - 16) / 10);

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
	Vector2 currentPos = GetPosition();
	switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//formula for bouncing off of player
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	case(ECOLLISIONLAYER_BULLET):
		//take damage from the bullet, bullet should also be destroyed on impact
		ModifyHealth(-1);
		if (GetHealth() <= 0)
			SetVisible(false);
		break;
	case(ECOLLISIONLAYER_ROCK):
		//formula for bouncing off of other rocks
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	case(ECOLLISIONLAYER_ENEMY):
		//formula for bouncing off of enemies
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	case(ECOLLISIONLAYER_HEALTH):
		//formula for bouncing off of health pickups
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	}
	SetPosition(currentPos);
}
