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
Vector2 SeekBehaviour::update(Actor* pTarget, Enemy* pSeeker)
{
	Vector2 playerPos = pTarget->GetPosition();


	//Seek Force
	Vector2 v2Dir = playerPos - pSeeker->GetPosition();	//Our basic direction getting. Where we want to go MINUS where we currently are
	v2Dir.normalise();
	v2Dir = v2Dir * pSeeker->GetMaxSpeed();
	Vector2 v2Force = v2Dir - pSeeker->GetVelocity();	//Force is = to our current direction MINUS our velocity

	return v2Force;
}

Vector2 SeekBehaviour::update(Vector2 targetPos, Enemy* pSeeker)
{
	//Seek Force
	Vector2 v2Dir = targetPos - pSeeker->GetPosition();	//Our basic direction getting. Where we want to go MINUS where we currently are
	v2Dir.normalise();
	v2Dir = v2Dir * pSeeker->GetMaxSpeed();
	Vector2 v2Force = v2Dir - pSeeker->GetVelocity();	//Force is = to our current direction MINUS our velocity

	return v2Force;
}