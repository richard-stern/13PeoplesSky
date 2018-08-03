#include "Rock.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Primitives.h"
#include "GUI.h"
#include "SmallRock.h"

Rock::Rock()
{
	//set health and max health to a random value between 2 and 4
	SetMaxHealth((rand() % 3) + 2);
	SetHealth(GetMaxHealth());

	//set self to visible
	SetVisible(true);

	//create children
	m_pSmallRock1 = new SmallRock;
	m_pSmallRock1->SetParent(this);
	AddChild(m_pSmallRock1);

	m_pSmallRock2 = new SmallRock;
	m_pSmallRock2->SetParent(this);
	AddChild(m_pSmallRock2);

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
	delete m_pSmallRock1;
	m_pSmallRock1 = nullptr;
	delete m_pSmallRock2;
	m_pSmallRock2 = nullptr;
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
		{
			SetVisible(false);
			GUI::GetInstance()->AddScore(100);
			m_pSmallRock1->SpawnSelf();
			m_pSmallRock2->SpawnSelf();
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

bool Rock::WrapAndRespawn()
{
	if (GameObject::WrapAndRespawn() && !m_bVisible) /* call base class wrap & respawn function */
	{
		if (!m_pSmallRock1->GetVisible() && !m_pSmallRock2->GetVisible())
		{
			m_pSmallRock1->SetPosition(Vector2(0, 0));
			m_pSmallRock2->SetPosition(Vector2(0, 0));
			m_pSmallRock1->SetVelocity(Vector2(0, 0));
			m_pSmallRock2->SetVelocity(Vector2(0, 0));
			m_pSmallRock1->SetHealth(GetMaxHealth());
			m_pSmallRock2->SetHealth(GetMaxHealth());
			SetHealth(GetMaxHealth()); /* reset health to full */
			SetVisible(true);
		}
	}
	return true;
}
