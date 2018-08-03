#include "BulletManager.h"
#include "Bullet.h"
#include "Vector2.h"
#include "Actor.h"
#include "Collider.h"

BulletManager::BulletManager(Actor* owner, int poolSize, ELayer layer, ELayer ignoreLayer)
{
	m_poolSize = poolSize;

	m_bulletPool = new Bullet*[m_poolSize];

	for (int i = 0; i < m_poolSize; i++)
	{
		m_bulletPool[i] = new Bullet(layer, ignoreLayer);
		AddChild(m_bulletPool[i]);
	}

	m_owner = owner;
}

BulletManager::~BulletManager()
{
	for (int i = 0; i < m_poolSize; i++)
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
	for (int i = 0; i < m_poolSize; i++)
	{
		if (!m_bulletPool[i]->GetVisible())
		{
			m_bulletPool[i]->Shoot(position, velocity, m_owner->GetVelocity());
			break;
		}
	}
}

void BulletManager::Update(float deltaTime)
{
	/*for (int i = 0; i < POOL_SIZE; i++)
	{
		m_bulletPool[i]->Update(deltaTime);
	}*/
	GameObject::Update(deltaTime);
}

void BulletManager::Draw(aie::Renderer2D* pRenderer)
{
	GameObject::Draw(pRenderer);
}
