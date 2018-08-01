#include "Bullet.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "TextureManager.h"
#include "Camera.h"

Bullet::Bullet()
{
	m_bWrapAndRespawn = false;
	m_bVisible = false;

	TextureManager* textureMan = TextureManager::GetInstance();
	m_pTexture = textureMan->LoadTexture("./textures/bullet");
}

Bullet::~Bullet()
{
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
// Bullet is set to not visible when it collides
//-----------------
void Bullet::OnCollision(Actor* other)
{
	m_bVisible = false;
}