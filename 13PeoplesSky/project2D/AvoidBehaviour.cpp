#include "AvoidBehaviour.h"
#include "FleeBehaviour.h"
#include "Vector2.h"
#include "Actor.h"

AvoidBehaviour::AvoidBehaviour()
{
	m_flee = new FleeBehaviour;
}


AvoidBehaviour::~AvoidBehaviour()
{
	delete m_flee;
}


//This function uses the exact same code as the PursueBehaviour, only that it flees instead of seeks once it's found it's targets destination
Vector2 AvoidBehaviour::update(Actor* pTarget, Enemy* pAvoider)
{
	Vector2 ToPlayer = pTarget->GetPosition() - pAvoider->GetPosition(); //Getting the distance between the pursuer and the target

	double RelativeHeading = pAvoider->GetVelocity().dot(pTarget->GetVelocity());
	
	//Here we are almost looking into the future to see where the pursued object is going to be in the future, and we will be seeking that location
	double LookAheadTime = ToPlayer.magnitude() / (pAvoider->GetMaxSpeed() + pTarget->GetVelocity().magnitude());

	return m_flee->update(pTarget->GetPosition() + pTarget->GetVelocity() * LookAheadTime, pAvoider);
}
