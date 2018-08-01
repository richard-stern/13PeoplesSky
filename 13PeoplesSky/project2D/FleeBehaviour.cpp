#include "FleeBehaviour.h"
#include "Vector2.h"
#include "Actor.h"
#include "Enemy.h"


FleeBehaviour::FleeBehaviour()
{
}

FleeBehaviour::~FleeBehaviour()
{
}


//-------------------------------------------------------------------------------------
//		UPDATE FUNCTION
// Takes in 2 agent pointers, one being the player that is being fled, and the
// other being the enemy object that is doing the fleeing
//-------------------------------------------------------------------------------------
Vector2 FleeBehaviour::update(Actor* pPlayer, Enemy* pEnemy)
{
	Vector2 playerPos = pPlayer->GetPosition();


	//Flee Force
	Vector2 v2Dir = pEnemy->GetPosition() - playerPos;	//Our basic direction getting. Where we want to go MINUS where we currently are
	v2Dir.normalise();
	v2Dir = v2Dir * pEnemy->getMaxSpeed();
	Vector2 v2Force = v2Dir - pEnemy->GetVelocity();	//Force is = to our current direction MINUS our velocity

	return v2Force;
}