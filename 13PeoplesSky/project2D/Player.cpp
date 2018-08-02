#include <Input.h>
#include "Player.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Turret.h"
#include "Collider.h"

Player::Player()
{
	SetVisible(true);
	SetHealth(GetMaxHealth());
	// Request the TextureManager for the ship texture 
	// Getting TextureManager Instance
	TextureManager* textureInstance = TextureManager::GetInstance();
	// Initializing m_pTexture to ship texture
	SetTexture(textureInstance->LoadTexture("./textures/ship.png"));
		
	// Create turret
	m_ShipTurret = new Turret();
	this->AddChild(m_ShipTurret);
	m_ShipTurret->SetParent(this);

	// Setting initial position
	//m_m3LocalMatrix.SetPosition(Vector2(640.0f, 360.0f));

	// Default Values
	m_v2Velocity = Vector2(0.0f, 0.0f);
	m_fAngularVelocity = 0.0f;
	m_fMaxSpeed = 300.0f;
	m_fMaxRot = 1.0f;
	m_fMass = 0.5f;
	m_fDrag = 0.5f;
}

Player::~Player()
{
	// Deleting the turret
	delete m_ShipTurret;
}

void Player::Update(float deltaTime)
{
	// Getting instance on input and camera
	aie::Input* input = aie::Input::getInstance();
	Camera* m_cLevelCamera = Camera::GetInstance();


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
	{
		v2ForceSum += m_m3GlobalMatrix.GetFacing2D() * m_fMaxSpeed;
	}
		
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		v2ForceSum -= m_m3GlobalMatrix.GetFacing2D() * m_fMaxSpeed;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		fForceRot += m_fMaxRot;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		fForceRot -= m_fMaxRot;
	}

	// Calculating velocity
	v2Acceleration.x = v2ForceSum.x / m_fMass;
	v2Acceleration.y = v2ForceSum.y / m_fMass;
	v2Dampening = (m_v2Velocity * m_fDrag) * -1.0f;
	m_v2Velocity += (v2Acceleration + v2Dampening) * deltaTime;


	// Calculating Rotation
	fAcceleration = fForceRot / m_fMass;
	fDampening = (m_fAngularVelocity * m_fDrag) * -1.0f;
	m_fAngularVelocity += (fAcceleration + fDampening) * deltaTime;

	// This code is done in Actor
	/*m_v2Position = m_v2Position + (m_v2Velocity * deltaTime);
	m_m3Position.SetPosition(m_v2Position);
	m_m3LocalMatrix = m_m3Scale * m_m3Position;*/
	// code end

	// Calls the actor's update
	Actor::Update(deltaTime);

	// Setting positon of camera
	m_cLevelCamera->SetPosition(
		m_m3LocalMatrix.GetPosition().x, 
		m_m3LocalMatrix.GetPosition().y
	);

}

void Player::OnCollision(Actor* collidingObject, CollisionData* data)
{

}
