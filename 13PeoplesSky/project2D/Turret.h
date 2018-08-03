#pragma once
#include "Renderer2D.h"
#include "Actor.h"

#define FIRE_RATE 0.12f

class BulletManager;
class Player;

class Turret : public Actor
{
public:
	Turret(Player* pPlayer);		//constuctor that sets position and takes in a player pointer to give to the bullets
	~Turret();

	void Update(float fDeltaTime);		//updates the turrets rotation, checks for shoot input
	//void Draw(aie::Renderer2D* pRenderer);		//draws turret

	inline void OnCollision(Actor* collidingObject, CollisionData* data) {};		//doesnt do anything, needed for override

private:
	BulletManager * m_pBullets;		//bulletpool that is responsible for bullet management

	float timer;
};

