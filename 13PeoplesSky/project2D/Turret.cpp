#include "Turret.h"
#include "Input.h"
#include "Matrix3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "TextureManager.h"
#include "BulletManager.h"
#include "Camera.h"

Turret::Turret() : Actor()
{
	m_pBullets = new BulletManager();
	AddChild(m_pBullets);		//adds bullets to child list for updating
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
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fRot), sinf(fRot)));		//calls the shoot function in the bullet manager
	}

	Vector2 mousePos = Camera::GetInstance()->GetPosition();
	mousePos.x += input->getMouseX();
	mousePos.y += input->getMouseY();

	Vector2 v2Diff;
	v2Diff = mousePos - GetGlobalTransform().GetPosition();

	float fTurn = (float)atan2(v2Diff.y, v2Diff.x);		//gets new rotation
	//m_m3LocalMatrix.SetRotate2D(fTurn);		//sets the new rotation
	m_fRotation = fTurn - M_PI/2;
	Actor::Update(fDeltaTime);		//update the actor
}

//void Turret::Draw(aie::Renderer2D* pRenderer)
//{
//	pRenderer->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix, 0, 0, 0, 0.5, 0.2f);
//}