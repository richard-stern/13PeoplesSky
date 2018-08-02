#include "TestActor.h"
#include <iostream>
#include "Primitives.h"
#include "Input.h"

TestActor::TestActor()
{

}

TestActor::~TestActor()
{

}

void TestActor::Update(float deltatime) 
{
	aie::Input* input = aie::Input::getInstance();

	if(input->isKeyDown(aie::INPUT_KEY_W)) 
	{
		SetPosition(m_v2Position + Vector2(0, 500 * deltatime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		SetPosition(m_v2Position + Vector2(-500 * deltatime, 0));
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		SetPosition(m_v2Position + Vector2(0, -500 * deltatime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		SetPosition(m_v2Position + Vector2(500 * deltatime, 0));
	}
}

void TestActor::OnCollision(Actor* collidingActor, CollisionData* data) 
{
	std::cout << data->m_v2Normal.x << " , " << data->m_v2Normal.y << std::endl;
}