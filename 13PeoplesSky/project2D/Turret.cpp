#include "Turret.h"
#include "Input.h"
#include "Matrix3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "TextureManager.h"
#include "BulletManager.h"
#include "Camera.h"
#include "Player.h"
#include "Collider.h"

Turret::Turret(Player* pPlayer) : Actor()
{
	m_fTimer = 0.f;
	m_iAmmo = 1; //Starting ammo

	m_pBullets = new BulletManager(pPlayer, 20, ECOLLISIONLAYER_BULLET, ECOLLISIONLAYER_PLAYER);		//makes new bullet pool and passes in a player pointer
	AddChild(m_pBullets);		//adds bullets to child list for updating
	m_bWrapAndRespawn = false;		//stops bullets from wrapping around the screen
	m_pTexture = TextureManager::GetInstance()->LoadTexture("./textures/turret.png");		//loads texture from texture manager
}

Turret::~Turret()		//cleanup
{
	delete m_pBullets;
}

void Turret::Update(float fDeltaTime)
{
	aie::Input* input = aie::Input::getInstance();		//gets the input instance

	m_fTimer += fDeltaTime; //timer

	//gets rotation for both player rotation and bullet trajectory
	Vector2 mousePos = Camera::GetInstance()->GetPosition();
	mousePos.x += input->getMouseX();
	mousePos.y += input->getMouseY();

	Vector2 v2Diff;
	v2Diff = mousePos - GetGlobalTransform().GetPosition();

	float fTurn = (float)atan2(v2Diff.y, v2Diff.x);		//gets new rotation

	//change it back to: input->wasMouseButtonPressed(...) and remove: timer > f_v
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && m_fTimer > FIRE_RATE)		//checks for LMB input
	{
		float spread = ((float)(rand()) - 16384) / 524288.f; //Slight shotspread
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + spread), sinf(fTurn + spread)));		//calls the shoot function in the bullet manager
		m_fTimer = 0.f; //reset timer
	}
	//Special attack, only fire if we have some ammo
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT) && m_iAmmo > 0)
	{
		//Shoot a triangle
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.45f), sinf(fTurn + 0.45f)));
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.3f), sinf(fTurn + 0.3f)));
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.15f), sinf(fTurn + 0.15f)));
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn), sinf(fTurn)));
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.15f), sinf(fTurn - 0.15f)));
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.3f), sinf(fTurn - 0.3f)));
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.45f), sinf(fTurn - 0.45f)));

		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.4f), sinf(fTurn - 0.4f)) * 1.1f);
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.4f), sinf(fTurn + 0.4f)) * 1.1f);

		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.3f), sinf(fTurn - 0.3f)) * 1.2f);
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.3f), sinf(fTurn + 0.3f)) * 1.2f);

		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.2f), sinf(fTurn - 0.2f)) * 1.3f);
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.2f), sinf(fTurn + 0.2f)) * 1.3f);

		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn - 0.1f), sinf(fTurn - 0.1f)) * 1.4f);
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + 0.1f), sinf(fTurn + 0.1f)) * 1.4f);

		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn), sinf(fTurn)) * 1.5f);
		--m_iAmmo; //Lose ammo
	}

	m_fRotation = fTurn - (float)M_PI/2.0f - m_pParent->GetRotation();		//sets the new rotation
	Actor::Update(fDeltaTime);		//update the actor
}

//void Turret::Draw(aie::Renderer2D* pRenderer)
//{
//	pRenderer->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix, 0, 0, 0, 0.5, 0.2f);
//}

void Turret::AddAmmo(int _amount_of_ammo)
{
	m_iAmmo += _amount_of_ammo;
}

int Turret::GetAmmo()
{
	return m_iAmmo;
}