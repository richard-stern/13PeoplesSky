#include <Input.h>
#include "Player.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Turret.h"
#include "CollisionManager.h"
#include "Primitives.h"
#include "GUI.h"

Player::Player()
{
	// Default Values
	SetVisible(true);
	SetMaxHealth(6);
	SetHealth(GetMaxHealth());
	m_v2Velocity = Vector2(0.0f, 0.0f);
	m_fAngularVelocity = 0.0f;
	m_fMaxSpeed = 150.0f;
	m_fMaxRot = 4.7f;
	m_fMass = 0.5f;
	m_fDrag = 0.5f;
	m_fRotationDrag = 3.0f;
	m_timer = 0.0f;
	m_bPlayerInvincibility = true; // Player starts of as invincible
	m_fCollisionTime = m_timer;
	//m_fStationaryTime = m_timer;

	// Request the TextureManager for the ship texture 
	// Getting GUI, TextureManager and CollisionManager Instance
	CollisionManager* collisionMan = CollisionManager::GetInstance();
	TextureManager* textureInstance = TextureManager::GetInstance();
	GUI::GetInstance()->SetHealth(GetMaxHealth());

	// Initializing m_pTexture to ship texture
	SetTexture(textureInstance->LoadTexture("./textures/ship.png"));
		
	// Create turret
	m_ShipTurret = new Turret(this);
	this->AddChild(m_ShipTurret);
	m_ShipTurret->SetParent(this);
	
	// Collider things ask nick for it
	Collider* collider = new Collider;
	auto colliderNodes = collider->GetNodes();
	colliderNodes->push_back(new ColliderNode(Vector2(0, 40), 1));
	colliderNodes->push_back(new ColliderNode(Vector2(93 / 2, -8), 2));
	colliderNodes->push_back(new ColliderNode(Vector2(20, -40), 3));
	colliderNodes->push_back(new ColliderNode(Vector2(-20, -40), 4));
	colliderNodes->push_back(new ColliderNode(Vector2(-93 / 2, -8), 0));
	collider->SetLayer(ECOLLISIONLAYER_PLAYER);
	SetCollider(collider);
	collisionMan->AddObject(this);

	// animation stuff
	m_shipSheet = textureInstance->LoadTexture("./textures/ship flight-anim.png");
	m_shipSprite = m_pTexture;

	m_shipSize.x = (float)m_shipSprite->getWidth();
	m_shipSize.y = (float)m_shipSprite->getHeight();
}

Player::~Player()
{
	// Deleting the turret
	delete m_ShipTurret;
}

void Player::Update(float deltaTime)
{
	m_timer += deltaTime;
	// Getting instance on input and camera
	aie::Input* input = aie::Input::getInstance();
	Camera* cLevelCamera = Camera::GetInstance();

	// resetting values
	Vector2 v2Acceleration, v2Dampening, v2ForceSum = Vector2(0.0f, 0.0f);
	m_v2StationaryPos = GetPosition();

	// Variables for rotation calculation
	float fForceRot = 0.0f;
	float fAcceleration = 0.0f;
	float fDampening = 0.0f;

	// Getting latest position
	m_v2Position = m_m3LocalMatrix.GetPosition();

	// use WASD keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{

		v2ForceSum += m_m3GlobalMatrix.GetFacing2D() * m_fMaxSpeed;

		// set the texture to nullptr so we know it's animating
		SetTexture(nullptr);
	}
	else
	{
		// disable animation when W is not held
		SetTexture(m_shipSprite);
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
		v2ForceSum -= m_m3GlobalMatrix.GetFacing2D() * m_fMaxSpeed;

	if (input->isKeyDown(aie::INPUT_KEY_A))
		fForceRot += m_fMaxRot;

	if (input->isKeyDown(aie::INPUT_KEY_D))
		fForceRot -= m_fMaxRot;

	// Calculating velocity
	v2Acceleration.x = v2ForceSum.x / m_fMass;
	v2Acceleration.y = v2ForceSum.y / m_fMass;
	v2Dampening = (m_v2Velocity * m_fDrag) * -1.0f;
	m_v2Velocity += (v2Acceleration + v2Dampening) * deltaTime;


	// Calculating Rotation
	fAcceleration = fForceRot / m_fMass;
	fDampening = (m_fAngularVelocity * m_fRotationDrag) * -1.0f;
	m_fAngularVelocity += (fAcceleration + fDampening) * deltaTime;

	// Calls the actor's update
	Actor::Update(deltaTime);

	// Setting positon of camera
	cLevelCamera->SetPosition(
		m_m3LocalMatrix.GetPosition().x, 
		m_m3LocalMatrix.GetPosition().y
	);

	if (m_timer - m_fCollisionTime >= 3.0f)
	{
		// reset the colours of the ship and turret when
		// invincibility runs out so they're opaque again
		SetColor(0xffffffff);
		m_ShipTurret->SetColor(0xffffffff);
		m_bPlayerInvincibility = false;
	}

	if (m_bPlayerInvincibility)
	{
		// make the alpha go between 1/4 and 3/4
		float alpha = 1 - (fabsf(sinf(m_timer*10.0f)) / 2.0f + 0.125f);
		// convert things to unsigned chars because SetColor is weird
		const unsigned char w = 0xff;
		unsigned char a = (unsigned char)(alpha * 255);

		// apply the colour
		SetColor(a, w, w, w);
		m_ShipTurret->SetColor(a, w, w, w);
	}

	//if (m_timer - m_fStationaryTime >= 10.0f)
	//{
	//	m_fStationaryTime = m_timer;
	//	ModifyHealth(-2);
	//}
}

void Player::Draw(aie::Renderer2D* pRenderer)
{
	// if we're just drawing the sprite, we can simply draw and exit this
	if (m_pTexture == m_shipSprite)
	{
		Actor::Draw(pRenderer);
		return;
	}

	// we're accelerating, draw the animation!
	const int frameCount = 5;

	int thisFrame = (int)(m_timer * 15.0f) % frameCount;

	float xStart = thisFrame / (float)frameCount;
	float xWidth = 1.0f / frameCount;

	// set the UV rect to split up the spritesheet
	pRenderer->setUVRect(xStart, 0.0f, xWidth, 1.0f);

	pRenderer->setRenderColour(m_iColor);
	pRenderer->drawSpriteTransformed3x3(m_shipSheet, (float*)m_m3GlobalMatrix,
		m_shipSize.x, m_shipSize.y);

	// reset UV rect which was changed for animation
	pRenderer->setUVRect(0, 0, 1, 1);

	Actor::Draw(pRenderer);
}

void Player::OnCollision(Actor* collidingObject, CollisionData* data)
{
	Vector2 currentPos = GetPosition();
	Camera* cLevelCamera = Camera::GetInstance();
	switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_ENEMY_BULLET):
		//take damage from the bullet, bullet should also be destroyed on impact
		// Checking if invincibility is true or false 
		// if true
		if (!m_bPlayerInvincibility)
		{
			// setting the collision time
			m_fCollisionTime = m_timer;


			ModifyHealth(-1);
			m_bPlayerInvincibility = true;
		}

		// Camera shake feature
		cLevelCamera->SetShakeDuration(0.1f);
		cLevelCamera->SetShakeMagnitude(5.0f);

		if (GetHealth() <= 0)
			SetVisible(false);
		break;
	case(ECOLLISIONLAYER_ROCK):

		//formula for bouncing off of enemies
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		// formula end

		// Checking if invincibility is true or false 
			// if true
		if (!m_bPlayerInvincibility)
		{
			// setting the collision time
			m_fCollisionTime = m_timer;


			ModifyHealth(-1);
			m_bPlayerInvincibility = true;
		}

		// Camera shake feature
		cLevelCamera->SetShakeDuration(0.1f);
		cLevelCamera->SetShakeMagnitude(5.0f);

		if (GetHealth() <= 0)
			SetVisible(false);
		break;
	case(ECOLLISIONLAYER_ENEMY):

		//formula for bouncing off of enemies
		currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));
		// formula end

		// Checking if invincibility is true or false 
		// if true
		if (!m_bPlayerInvincibility)
		{
			// setting the collision time
			m_fCollisionTime = m_timer;

			ModifyHealth(-1);
			m_bPlayerInvincibility = true;
		}

		// Camera shake feature
		cLevelCamera->SetShakeDuration(0.1f);
		cLevelCamera->SetShakeMagnitude(5.0f);

		if (GetHealth() <= 0)
			SetVisible(false);
		break;

	case(ECOLLISIONLAYER_HEALTH):

		ModifyHealth(2);

		if (GetHealth() > GetMaxHealth())
			SetHealth(GetMaxHealth());

		break;

	case(ECOLLISIONLAYER_AMMO):

		m_fCollisionTime = m_timer;
		m_ShipTurret->AddAmmo(1);
		if (m_ShipTurret->GetAmmo() > 3)
		{
			m_ShipTurret->SetAmmo(3);
		}
		break;
	}

	GUI::GetInstance()->SetHealth(GetHealth());
	GUI::GetInstance()->SetAmmo(m_ShipTurret->GetAmmo());
	SetPosition(currentPos);
}