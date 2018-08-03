#include "Turret.h"
#include "Input.h"
#include "Matrix3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "TextureManager.h"
#include "BulletManager.h"
#include "Camera.h"
#include "Player.h"

Turret::Turret(Player* pPlayer) : Actor()
{
	timer = 0.f;
	m_pBullets = new BulletManager(pPlayer);		//makes new bullet pool and passes in a player pointer
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

	timer += fDeltaTime; //timer

	//gets rotation for both player rotation and bullet trajectory
	Vector2 mousePos = Camera::GetInstance()->GetPosition();
	mousePos.x += input->getMouseX();
	mousePos.y += input->getMouseY();

	Vector2 v2Diff;
	v2Diff = mousePos - GetGlobalTransform().GetPosition();

	float fTurn = (float)atan2(v2Diff.y, v2Diff.x);		//gets new rotation

	//change it back to: input->wasMouseButtonPressed(...) and remove: timer > f_v
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && timer > FIRE_RATE)		//checks for LMB input
	{
		float spread = ((float)(rand()) - 16384) / 524288.f; //Slight shotspread
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + spread), sinf(fTurn + spread)));		//calls the shoot function in the bullet manager
		timer = 0.f; //reset timer
	}

	m_fRotation = fTurn - (float)M_PI/2.0f - m_pParent->GetRotation();		//sets the new rotation
	Actor::Update(fDeltaTime);		//update the actor
}

//void Turret::Draw(aie::Renderer2D* pRenderer)
//{
//	pRenderer->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix, 0, 0, 0, 0.5, 0.2f);
//}