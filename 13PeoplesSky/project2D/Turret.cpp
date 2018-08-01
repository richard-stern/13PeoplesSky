#include "Turret.h"
#include "Input.h"
#include "Matrix3.h"

Turret::Turret(Vector2 v2Pos) : Actor(v2Pos)
{		//need to add in constructor parameters for base class and turret
		//create a bulletpool thing
	m_pBullets = new BulletManager();
	m_bWrapAndRespawn = false;
}

Turret::~Turret()
{
	delete m_pBullets;
}

void Turret::Update(float fDeltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT));
	{
		//need to know what parameters to pass though
		//m_pBullets.ShootBullet()		//
	}

	float fTurn = atan2(input->getMouseY(), input->getMouseX());

	m_m3LocalMatrix.SetRotate2D(fTurn);

	Actor::Update(fDeltaTime);
}

void Turret::Draw(aie::Renderer2D* pRenderer)
{
	aie::Input* input = aie::Input::getInstance();


}