#include "PursueBehaviour.h"
#include "SeekBehaviour.h"
#include "Vector2.h"
#include "Actor.h"


PursueBehaviour::PursueBehaviour()
{
	m_seek = new SeekBehaviour;
}


PursueBehaviour::~PursueBehaviour()
{
	delete m_seek;
}

Vector2 PursueBehaviour::update(Actor* pPlayer, Enemy* pEnemy)
{
	Vector2 ToPlayer = pPlayer->GetPosition() - pEnemy->GetPosition(); //Getting the distance between the pursuer and the target

	double RelativeHeading = pEnemy->GetVelocity().dot(pPlayer->GetVelocity());

	//If the pursued target is facing us, and travelling in our direction, then we don't need to pursue them, we can simply seek to their current position
	// We calculate whether or not they are facing us if they're heading is within 18 degrees of our own
	if (ToPlayer.dot(pEnemy->GetVelocity()) > 0 && RelativeHeading < -0.95) //acos(0.95)=18 degrees
	{
		return m_seek->update(pPlayer, pEnemy);
	}

	double LookAheadTime = ToPlayer.magnitude() / (pEnemy->GetMaxSpeed() + pPlayer->GetVelocity());  //Need to get player's speed, not it's velocity.
}
