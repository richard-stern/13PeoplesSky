#pragma once
#include "Renderer2D.h"
#include "Actor.h"
class BulletManager;

class Turret : public Actor
{
public:
	Turret();		//default constuctor that sets position
	~Turret();

	void Update(float fDeltaTime);		//updates the turrets rotation, checks for shoot input
	void Draw(aie::Renderer2D* pRenderer);		//draws turret

	inline void OnCollision(Actor* collidingObject, CollisionData* data) {};		//doesnt do anything, needed for override

private:
	BulletManager * m_pBullets;		//bulletpool that is responsible for bullet management
};

