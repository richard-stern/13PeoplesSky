#pragma once
#include "Actor.h"

class Texture;
class TextureManager;
class Player;
class Rock;
class PursueBehaviour;
class AvoidBehaviour;
class StateMachine;

class Enemy : public Actor
{
public:
	Enemy(Player* pPlayer, Rock** pRock);
	~Enemy();

	void Update(float DeltaTime);
	void OnCollision(Actor* collidingObject, CollisionData* data);

	float GetMaxSpeed();
	void SetMaxSpeed(float speed);

protected:
	//The speed at which the enemy will move
	float m_maxSpeed = 200.0f;
	Vector2 m_distToPlayer;
	float m_lengthToPlayer;
	Vector2 m_distToRock;
	float m_lengthToRock;

	float m_maxRot;
	int rockCount;

	Player* m_player;
	PursueBehaviour* m_pursue;
	AvoidBehaviour* m_avoid;
};