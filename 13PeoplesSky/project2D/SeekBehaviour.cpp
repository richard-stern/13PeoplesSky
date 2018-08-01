#include "SeekBehaviour.h"
#include "Vector2.h"
#include "Actor.h"

SeekBehaviour::SeekBehaviour()
{
}

SeekBehaviour::~SeekBehaviour()
{
}


//-------------------------------------------------------------------------------------
//		UPDATE FUNCTION
// Takes in 2 agent pointers, one being the player that is being sought, and the
// other being the enemy object that is doing the seeking
//-------------------------------------------------------------------------------------
Vector2 SeekBehaviour::update(Actor* pPlayer, Enemy* pEnemy)
{
	Vector2 playerPos = pPlayer->GetPosition();


	//Seek Force
	Vector2 v2Dir = playerPos - pEnemy->GetPosition();	//Our basic direction getting. Where we want to go MINUS where we currently are
	v2Dir.normalise();
	v2Dir = v2Dir * pEnemy->getMaxSpeed();
	Vector2 v2Force = v2Dir - pEnemy->GetVelocity();	//Force is = to our current direction MINUS our velocity

	return v2Force;
}

