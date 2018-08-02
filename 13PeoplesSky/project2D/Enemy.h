#pragma once
#include "Actor.h"

class Texture;
class TextureManager;
class Player;
class Rock;
class PursueBehaviour;
class AvoidBehaviour;

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	void Update(Player* pPlayer, Rock* pRock);
	void OnCollision(Actor* collidingObject, CollisionData* data);

	void SetMaxSpeed(float speed);
	float GetMaxSpeed();

protected:
	float m_maxSpeed = 300.0f;
	float m_distBetween;

	TextureManager* m_texture;
	PursueBehaviour* m_pursue;
	AvoidBehaviour* m_avoid;
};

