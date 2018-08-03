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
	m_fTimer = 0.0f;
	m_fAnimTimer = 0.0f;
	m_iAmmo = 1; //Starting ammo

	m_pBullets = new BulletManager(pPlayer, 20, ECOLLISIONLAYER_BULLET, ECOLLISIONLAYER_PLAYER);		//makes new bullet pool and passes in a player pointer
	AddChild(m_pBullets);		//adds bullets to child list for updating
	m_bWrapAndRespawn = false;		//stops bullets from wrapping around the screen
	m_pTexture = TextureManager::GetInstance()->LoadTexture("./textures/turret.png");		//loads texture from texture manager

																								// animation stuff
	m_turretSheet = TextureManager::GetInstance()->LoadTexture("./textures/turret shoot-anim.png");
	m_turretSprite = m_pTexture;

	m_v2TurretSize.x = (float)m_turretSprite->getWidth();
	m_v2TurretSize.y = (float)m_turretSprite->getHeight();

	m_bFiring = false;
}

Turret::~Turret()		//cleanup
{
	delete m_pBullets;
}

void Turret::Update(float fDeltaTime)
{
	aie::Input* input = aie::Input::getInstance();		//gets the input instance

	m_fTimer += fDeltaTime; //timer
	m_fAnimTimer += fDeltaTime;

	//gets rotation for both player rotation and bullet trajectory
	Vector2 mousePos = Camera::GetInstance()->GetPosition();
	mousePos.x += input->getMouseX();
	mousePos.y += input->getMouseY();

	Vector2 v2Diff;
	v2Diff = mousePos - GetGlobalTransform().GetPosition();

	float fTurn = (float)atan2(v2Diff.y, v2Diff.x);		//gets new rotation


	if (!m_bFiring)
		m_fAnimTimer = 0.0f;
	m_pTexture = m_turretSprite;

	//change it back to: input->wasMouseButtonPressed(...) and remove: timer > f_v
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && m_fTimer > FIRE_RATE)		//checks for LMB input
	{
		float spread = ((float)(rand()) - 16384) / 524288.f; //Slight shotspread
		m_pBullets->ShootBullet(GetGlobalTransform().GetPosition(), Vector2(cosf(fTurn + spread), sinf(fTurn + spread)));		//calls the shoot function in the bullet manager
		m_fTimer = 0.f; //reset timer

		m_pTexture = nullptr;
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

		m_turretSprite = m_turretSheet;
	}

	m_fRotation = fTurn - (float)M_PI/2.0f - m_pParent->GetRotation();		//sets the new rotation
	Actor::Update(fDeltaTime);		//update the actor
}

void Turret::Draw(aie::Renderer2D* pRenderer)
{
	// if we're just drawing the sprite, we can simply draw and exit this
	if (m_pTexture == m_turretSprite)
	{
		Actor::Draw(pRenderer);
		return;
	}

	// we're firing, draw the animation!
	const int frameCount = 5;

	int thisFrame = (int)(m_fAnimTimer * 1.0f) % frameCount;

	if (thisFrame == 0)
		m_bFiring = true;

	if (thisFrame == frameCount)
		m_bFiring = false;

	float xStart = thisFrame / (float)frameCount;
	float xWidth = 1.0f / frameCount;

	// set the UV rect to split up the spritesheet
	pRenderer->setUVRect(xStart, 0.0f, xWidth, 1.0f);

	pRenderer->setRenderColour(m_iColor);
	pRenderer->drawSpriteTransformed3x3(m_turretSheet, (float*)m_m3GlobalMatrix,
		m_v2TurretSize.x, m_v2TurretSize.y);

	// reset UV rect which was changed for animation
	pRenderer->setUVRect(0, 0, 1, 1);

	Actor::Draw(pRenderer);
}

void Turret::AddAmmo(int _amount_of_ammo)
{
	m_iAmmo += _amount_of_ammo;
}

void Turret::SetAmmo(int _ammo)
{
	m_iAmmo = _ammo;
}

int Turret::GetAmmo()
{
	return m_iAmmo;
}