#include "BulletManager.h"
#include "Bullet.h"
#include "Vector2.h"

BulletManager::BulletManager()
{
	m_bulletPool = new Bullet*[POOL_SIZE];

	for (int i = 0; i < POOL_SIZE; i++)
	{
		m_bulletPool[i] = new Bullet();
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

void BulletManager::ShootBullet(Vector2 position, Vector2 velocity)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!m_bulletPool[i].GetVisible())
		{
			m_bulletPool[i]->Shoot(position, velocity);
			break;
		}
	}
}
