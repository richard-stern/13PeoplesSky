#include "BulletManager.h"
#include "Bullet.h"
#include "Vector2.h"

BulletManager::BulletManager()
{
	m_bulletPool = new Bullet*[POOL_SIZE];

	for (int i = 0; i < POOL_SIZE; i++)
	{
		m_bulletPool[i] = new Bullet();
		//AddChild(m_bulletPool[i]);
	}
}

BulletManager::~BulletManager()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		delete m_bulletPool[i];
	}
	delete[] m_bulletPool;
}

//-----------------
// Find a bullet the first avaliable bullet in the pool and shoot it
//-----------------
void BulletManager::ShootBullet(Vector2 position, Vector2 velocity)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!m_bulletPool[i]->GetVisible())
		{
			m_bulletPool[i]->Shoot(position, velocity);
			break;
		}
	}
}

void BulletManager::Update(float deltaTime)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		m_bulletPool[i]->Update(deltaTime);
	}
	GameObject::Update(deltaTime);
}
