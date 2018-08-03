#include "Bullet.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "TextureManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Primitives.h"

Bullet::Bullet(ELayer layer, ELayer ignoreLayer)
{
	m_bWrapAndRespawn = false;
	m_bVisible = false;
	m_fDrag = 0.0f;

	TextureManager* textureMan = TextureManager::GetInstance();
	m_pTexture = textureMan->LoadTexture("./textures/bullet.png");	

	Collider* collider = new Collider();

	auto colliderNodes = collider->GetNodes();
	
	colliderNodes->push_back(new ColliderNode(Vector2(-2.5, 2.5), 1));
	colliderNodes->push_back(new ColliderNode(Vector2(2.5, 2.5), 2));
	colliderNodes->push_back(new ColliderNode(Vector2(2.5, -2.5), 3));
	colliderNodes->push_back(new ColliderNode(Vector2(-2.5, -2.5), 0));

	collider->SetLayer(layer);
	collider->SetIgnoreLayer(ignoreLayer);

	SetCollider(collider);

	CollisionManager* cm = CollisionManager::GetInstance();
	cm->AddObject(this);
}

void Bullet::Update(float deltaTime)
{
	Camera* camera = Camera::GetInstance();

	Vector2 pos = m_v2Position;
	pos -= camera->GetPosition();

	Actor::Update(deltaTime);

	if (pos.x > 1280 || pos.x < 0 || pos.y > 720 || pos.y < 0)
	{
		m_bVisible = false;
	}

	if (m_collided)
	{
		m_bVisible = false;
	}
	m_collided = false;

	GetCollider()->UpdateBounds(&m_m3GlobalMatrix);
}

//-----------------
// Set new position and velocity
// Set the bullet to visible
//-----------------
void Bullet::Shoot(Vector2 position, Vector2 velocity, Vector2 ownerVelocity)
{
	m_v2Position = position;
	m_v2Velocity = velocity * 600;
	m_v2Velocity += ownerVelocity;
	
	m_bVisible = true;
}

//-----------------
// Bullet is set to not visible when it collides with an
// enemy, health pack or a rock
//-----------------
void Bullet::OnCollision(Actor* collidingObject, CollisionData* _collision_data)
{
	ELayer layer = GetCollider()->GetLayer();
	bool playerBullet = false;
	if (layer == ECOLLISIONLAYER_BULLET)
	{
		playerBullet = true;
	}

	switch (collidingObject->GetCollider()->GetLayer())
	{
	
	case(ECOLLISIONLAYER_ENEMY):
		if (playerBullet)
			m_collided = true;
		break;
	case(ECOLLISIONLAYER_PLAYER):
		if (!playerBullet)
			m_collided = true;
		break;

	case(ECOLLISIONLAYER_HEALTH):
		m_collided = true;
		break;

	case(ECOLLISIONLAYER_ROCK):
		m_collided = true;
		break;
	}
	
}