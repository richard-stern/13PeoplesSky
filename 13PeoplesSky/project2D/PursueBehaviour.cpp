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

Vector2 PursueBehaviour::update(Actor* pTarget, Enemy* pPursuer)
{
	Vector2 ToPlayer = pTarget->GetPosition() - pPursuer->GetPosition(); //Getting the distance between the pursuer and the target

	//float RelativeHeading = pPursuer->GetVelocity().dot(pTarget->GetVelocity());
	float RelativeHeading = pPursuer->GetGlobalTransform().GetFacing2D().dot(pTarget->GetGlobalTransform().GetFacing2D());

	//If the pursued target is facing us and travelling in our direction, then we don't need to pursue them, we can simply seek to their current position
	// We calculate whether or not they are facing us if they're heading is within 18 degrees of our own
	if (ToPlayer.dot(pPursuer->GetGlobalTransform().GetFacing2D()) > 0 && RelativeHeading < -0.95) //acos(0.95)=18 degrees
	{
		return m_seek->update(pTarget, pPursuer);
	}

	//Here we are seeing where the pursued object is going to be in the future, and we will be seeking that location
	float LookAheadTime = ToPlayer.magnitude() / (pPursuer->GetMaxSpeed() + pTarget->GetVelocity().magnitude());

	return m_seek->update(pTarget->GetPosition() + pTarget->GetVelocity() * LookAheadTime, pPursuer);
}