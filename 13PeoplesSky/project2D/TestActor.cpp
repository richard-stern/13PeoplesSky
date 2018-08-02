#include "TestActor.h"
#include <iostream>

TestActor::TestActor()
{

}

TestActor::~TestActor()
{

}

void TestActor::OnCollision(Actor* collidingActor, CollisionData* data) 
{
	std::cout << "Collision!" << std::endl;
}