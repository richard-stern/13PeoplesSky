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
Vector2 FleeBehaviour::update(Actor* pTarget, Enemy* pFleeing)
{
	Vector2 playerPos = pTarget->GetPosition();


	//Flee Force
	Vector2 v2Dir = pFleeing->GetPosition() - playerPos;	//Our basic direction getting. Where we want to go MINUS where we currently are
	v2Dir.normalise();
	v2Dir = v2Dir * pFleeing->GetMaxSpeed();
	Vector2 v2Force = v2Dir - pFleeing->GetVelocity();	//Force is = to our current direction MINUS our velocity

	return v2Force;
}

//We need this alternate update function for it to work with our avoid function, as we need to pass in a vector, not an actor
Vector2 FleeBehaviour::update(Vector2 targetPos, Enemy* pFleeing)
{
	//Seek Force
	Vector2 v2Dir = pFleeing->GetPosition() - targetPos;	//Our basic direction getting. Where we want to go MINUS where we currently are
	v2Dir.normalise();
	v2Dir = v2Dir * pFleeing->GetMaxSpeed();
	Vector2 v2Force = v2Dir - pFleeing->GetVelocity();	//Force is = to our current direction MINUS our velocity

	return v2Force;
}