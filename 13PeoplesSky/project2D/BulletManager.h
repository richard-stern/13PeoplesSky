#pragma once

#define POOL_SIZE 10

class Bullet;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	//-----------------
	// Searches the bullet pool for an inactive bullet and runs the shoot command
	// Params: Input for the shoot command
	//			initial position
	//			initial velocity
	//-----------------
	void ShootBullet(Vector2 position, Vector2 velocity);

	Bullet** m_bulletPool;
};

