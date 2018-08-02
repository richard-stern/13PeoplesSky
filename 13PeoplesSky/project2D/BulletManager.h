#pragma once
#include "Vector2.h"
#include "Actor.h"

#define POOL_SIZE 10

class Bullet;

class BulletManager : public Actor
{
public:
	BulletManager();
	~BulletManager();

	//-----------------
	// Searches the bullet pool for an inactive bullet and runs the shoot command
	// Params: Input for the shoot command
	//			initial position (turret position)
	//			initial velocity (turret facing)
	//-----------------
	void ShootBullet(Vector2 position, Vector2 velocity);

	void Update(float deltaTime);

	Bullet** m_bulletPool;
};

