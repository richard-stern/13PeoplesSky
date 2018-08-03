#include "SmallRock.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Primitives.h"
#include "GUI.h"

SmallRock::SmallRock()
{
	//set health and max health to a random value between 1 and 2
	SetMaxHealth((rand() % 2) + 1);
	SetHealth(GetMaxHealth());

	//set self to invisible
	SetVisible(false);

	//set wrap to true
	m_bWrapAndRespawn = true;

	//get instance of texture manager
	TextureManager* textureMan = TextureManager::GetInstance();
	CollisionManager* collisionMan = CollisionManager::GetInstance();

	//set texture to rock texture
	//TEMP TEXTURE, replace when new texture made
	SetTexture(textureMan->LoadTexture("./textures/rock_medium.png"));

	//Sets velocity to zero
	SetVelocity(Vector2(0, 0));

	//Sets position to zero
	SetPosition(Vector2(0, 0));

	//Sets random rotation in radians
	SetRotation(((float)(rand() % 32) - 16) / 10);

	//Sets random angular rotation
	SetAngularVelocity(((float)(rand() % 32) - 16) / 10);

	//Creates a collider, sets neccesary variables. 
	PrimRectangle* collider = new PrimRectangle(32, 32);
	collider->SetLayer(ECOLLISIONLAYER_ROCK);
	SetCollider(collider);
	collisionMan->AddObject(this);

	m_destroyed = false;
}


SmallRock::~SmallRock()
{
}

void SmallRock::OnCollision(Actor * collidingObject, CollisionData * data)
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
		{
			m_destroyed = true;
			GUI::GetInstance()->AddScore(50);
		}
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

void SmallRock::SpawnSelf(Vector2 position)
{
	m_v2Position = position;
	SetVelocity(Vector2((float)((rand() % 200) - 50), (float)((rand() % 200) - 50)));
	SetVisible(true);
}

bool SmallRock::WrapAndRespawn()
{
	GameObject::WrapAndRespawn();
	return true;
}

void SmallRock::Update(float deltatime)
{
	if (m_destroyed)
	{
		m_bVisible = false;
	}
	m_destroyed = false;

	Actor::Update(deltatime);
}

void SmallRock::Draw(aie::Renderer2D *renderer)
{
	Actor::Draw(renderer);
}