#include "Turret.h"
#include "Input.h"
#include "Matrix3.h"
#include <math.h>
#include "TextureManager.h"
#include "BulletManager.h"

Turret::Turret() : Actor()
{
	m_pBullets = new BulletManager();
	m_bWrapAndRespawn = false;		//stops bullets from wrapping around the screen
	m_pTexture = TextureManager::GetInstance()->LoadTexture("./textures/BarrelBlue.png");		//loads texture from texture manager
}

Turret::~Turret()		//cleanup
{
	delete m_pBullets;
}

void Turret::Update(float fDeltaTime)
{
	aie::Input* input = aie::Input::getInstance();		//gets the input instance
	float fRot = GetRotation();		//gets rotation for bullet trajectory

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))		//checks for LMB input
	{
		m_pBullets->ShootBullet(GetPosition(), Vector2(cosf(fRot), sinf(fRot)));		//calls the shoot function in the bullet manager
	}

	float fTurn = (float)atan2(input->getMouseY(), input->getMouseX());		//gets new rotation

	m_m3LocalMatrix.SetRotate2D(fTurn);		//sets the new rotation

	Actor::Update(fDeltaTime);		//update the actor
}

void Turret::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix);
}