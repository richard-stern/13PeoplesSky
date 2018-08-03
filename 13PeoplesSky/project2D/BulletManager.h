#pragma once
#include "Vector2.h"
#include "GameObject.h"

class Bullet;
class Actor;
enum ELayer;

class BulletManager : public GameObject
{
public:

	BulletManager(Actor* owner, int poolSize, ELayer layer, ELayer ignoreLayer);
	~BulletManager();

	//-----------------
	// Searches the bullet pool for an inactive bullet and runs the shoot command
	// Params: Input for the shoot command
	//			initial position (turret position)
	//			initial velocity (turret facing)
	//-----------------
	void ShootBullet(Vector2 position, Vector2 velocity);

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* pRenderer);

	Bullet** m_bulletPool;
	Actor* m_owner;

	int m_poolSize;
};

