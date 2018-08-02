#pragma once
#include "Actor.h"

class TextureManager;
class Player;
class Rock;

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	void Update(Player* pPlayer);
	void OnCollision();

	float GetMaxSpeed();



private:
	float m_maxSpeed = 300.0f;
	TextureManager* pTexture;
};

