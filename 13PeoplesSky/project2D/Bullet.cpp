#include "Bullet.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "TextureManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Primitives.h"

Bullet::Bullet()
{
	m_bWrapAndRespawn = false;
	m_bVisible = false;
	m_fDrag = 0.0f;

	TextureManager* textureMan = TextureManager::GetInstance();
	m_pTexture = textureMan->LoadTexture("./textures/bullet");	

	Collider* collider = new Collider();

	auto colliderNodes = collider->GetNodes();
	
	colliderNodes->push_back(new ColliderNode(Vector2(-2.5, 2.5), 1));
	colliderNodes->push_back(new ColliderNode(Vector2(2.5, 2.5), 2));
	colliderNodes->push_back(new ColliderNode(Vector2(2.5, -2.5), 3));
	colliderNodes->push_back(new ColliderNode(Vector2(-2.5, -2.5), 0));

	collider->SetLayer(ECOLLISIONLAYER_BULLET);
	collider->SetIgnoreLayer(ECOLLISIONLAYER_PLAYER);

	SetCollider(collider);
}

void Bullet::Update(float deltaTime)
{
	Camera* camera = Camera::GetInstance();

	Vector2 pos = m_m3LocalMatrix.GetPosition();
	pos -= camera->GetPosition();

	if (pos.x > 1280 || pos.x < 0 || pos.y > 720 || pos.y < 0)
	{
		m_bVisible = false;
	}

	Actor::Update(deltaTime);
	GetCollider()->UpdateBounds(&m_m3GlobalMatrix);
}

//-----------------
// Set new position and velocity
// Set the bullet to visible
//-----------------
void Bullet::Shoot(Vector2 position, Vector2 velocity)
{
	m_m3LocalMatrix.SetPosition(position);
	m_v2Velocity = velocity;
	m_bVisible = true;
}

//-----------------
// Bullet is set to not visible when it collides with an
// enemy, health pack or a rock
//-----------------
void Bullet::OnCollision(Actor* collidingObject, CollisionData* _collision_data)
{
	switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_ENEMY):
		m_bVisible = false;
		break;

	case(ECOLLISIONLAYER_HEALTH):
		m_bVisible = false;
		break;

	case(ECOLLISIONLAYER_ROCK):
		m_bVisible = false;
		break;
	}
	
}