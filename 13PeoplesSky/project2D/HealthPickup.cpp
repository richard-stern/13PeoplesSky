#include "HealthPickup.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Primitives.h"

HealthPickup::HealthPickup()
{
	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();
	CollisionManager* collisionMan = CollisionManager::GetInstance();

	//set self to visible
	SetVisible(true);

	//set wrap to true
	m_bWrapAndRespawn = true;

	//set texture to health texture
	//TEMP TEXTURE, replace when new texture made
	SetTexture(textureMan->LoadTexture("./textures/health.png"));

	//Sets random velocity, change numbers as neccesary
	SetVelocity(Vector2((float)((rand() % 72) - 36), (float)((rand() % 72) - 36)));

	//Creates a collider, sets neccesary variables. 
	PrimRectangle* collider = new PrimRectangle(32, 32);
	collider->SetLayer(ECOLLISIONLAYER_HEALTH);
	SetCollider(collider);
	collisionMan->AddObject(this);
}

HealthPickup::~HealthPickup()
{
}

void HealthPickup::Update(float deltaTime)
{
	if (m_collided)
	{
		m_bVisible = false;
	}
	m_collided = false;

	Actor::Update(deltaTime);
}

void HealthPickup::OnCollision(Actor* collidingObject, CollisionData* data)
{
	Vector2 currentPos = GetPosition();
	switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;
	case(ECOLLISIONLAYER_PLAYER):
		//destroy health pickup
		//player should also gain health, code done in player class
		m_collided = true;
		break;
	case(ECOLLISIONLAYER_BULLET):
		//destroy health pickup
		//bullet should also be destroyed, code would be done in bullet class
		m_collided = true;
		break;
	case(ECOLLISIONLAYER_ROCK):
		//formula for bouncing off of rocks
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	case(ECOLLISIONLAYER_ENEMY):
		//formula for bouncing off of enemies
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	case(ECOLLISIONLAYER_HEALTH):
		//formula for bouncing off of other health pickups
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		break;
	}
	SetPosition(currentPos);
}
