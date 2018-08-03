#include <Input.h>
#include <iostream>
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
	SetMaxHealth(100);
	SetHealth(GetMaxHealth());
	m_v2Velocity = Vector2(0.0f, 0.0f);
	m_fAngularVelocity = 0.0f;
	m_fMaxSpeed = 150.0f;
	m_fMaxRot = 4.7f;
	m_fMass = 0.5f;
	m_fDrag = 0.5f;
	m_fRotationDrag = 3.0f;
	m_timer = 0.0f;
	m_bPlayerInvincibility = false;

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

	// Variables for rotation calculation
	float fForceRot = 0.0f;
	float fAcceleration = 0.0f;
	float fDampening = 0.0f;

	// Getting latest position
	m_v2Position = m_m3LocalMatrix.GetPosition();

	// use WASD keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_W))
		v2ForceSum += m_m3GlobalMatrix.GetFacing2D() * m_fMaxSpeed;

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
		SetColor(0xffffffff);
		m_bPlayerInvincibility = false;
	}

	if (m_bPlayerInvincibility)
	{
		float alpha = fabsf(sinf(m_timer*10.0f)) / 2.0f + 0.125f;
		const unsigned char w = 0xff;
		SetColor((char)(alpha * 255), w, w, w);
	}
}

void Player::OnCollision(Actor* collidingObject, CollisionData* data)
{
	Vector2 currentPos = GetPosition();
	Camera* cLevelCamera = Camera::GetInstance();
	switch (collidingObject->GetCollider()->GetLayer())
	{
		//case(ECOLLISIONLAYER_BULLET):
			//take damage from the bullet, bullet should also be destroyed on impact
			//ModifyHealth(-1);
			//if (GetHealth() <= 0)
			//	SetVisible(false);
			//break;
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


			ModifyHealth(-10);
			std::cout << "Player health -10, Health is " << GetHealth() << std::endl;
			std::cout << "Player is Invincible" << std::endl;
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

			ModifyHealth(-10);
			std::cout << "Player health -10, Health is " << GetHealth() << std::endl;
			std::cout << "Player is Invincible" << std::endl;
			m_bPlayerInvincibility = true;
		}

		// Camera shake feature
		cLevelCamera->SetShakeDuration(0.1f);
		cLevelCamera->SetShakeMagnitude(5.0f);

		if (GetHealth() <= 0)
			SetVisible(false);
		break;
	case(ECOLLISIONLAYER_HEALTH):

		m_fCollisionTime = m_timer;

		ModifyHealth(30);
		std::cout << "Player health 10, Health is " << GetHealth() << std::endl;

		if (GetHealth() > GetMaxHealth())
			SetHealth(GetMaxHealth());

		break;
	}
	GUI::GetInstance()->SetHealth(GetHealth());
	SetPosition(currentPos);
}
