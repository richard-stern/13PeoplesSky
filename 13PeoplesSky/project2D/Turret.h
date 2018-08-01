#pragma once
#include "Renderer2D.h"
#include "Actor.h"
#include "BulletManager.h"

class Turret : public Actor
{
public:
	Turret(Vector2 v2Pos);
	~Turret();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);

private:
	BulletManager * m_pBullets;
};

