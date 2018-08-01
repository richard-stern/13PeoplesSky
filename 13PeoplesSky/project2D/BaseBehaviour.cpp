#include "BaseBehaviour.h"
#include "Actor.h"
#include "Matrix3.h"
#include "Vector2.h"


BaseBehaviour::BaseBehaviour()
{
}


BaseBehaviour::~BaseBehaviour()
{
}

Vector2 BaseBehaviour::GetHeading()
{
	Matrix3 heading;
	Vector2 facing;

	facing = heading.GetFacing2D();
	
	return facing;
}
