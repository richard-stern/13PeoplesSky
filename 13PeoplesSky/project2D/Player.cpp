#include <Input.h>
#include "Player.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Turret.h"

Player::Player()
{
	// Create turret
	m_ShipTurret = new Turret();

	this->AddChild(m_ShipTurret);
	m_ShipTurret->SetParent(this);
	// Request the TextureManager for the ship texture 
	// Getting TextureManager Instance
	TextureManager* textureInstance = TextureManager::GetInstance();
	// Initializing m_pTexture to ship texture
	m_pTexture = textureInstance->LoadTexture("./ship.png");

	// Setting initial position
	m_m3LocalMatrix.SetPosition(Vector2(640.0f, 360.0f));

	// Default Values
	m_v2Velocity = Vector2(0.0f, 0.0f);
	m_fMaxSpeed = m_v2Velocity.magnitude();
	m_fMass = 0.5f;
	m_fDrag = 0.5f;
}

Player::~Player()
{
	// Deleting the turret
	delete m_ShipTurret;
}

void Player::update(float deltaTime)
{
	// Getting instance on input and camera
	aie::Input* input = aie::Input::getInstance();
	Camera* m_cLevelCamera = Camera::GetInstance();

	// Getting latest position
	m_v2Position = m_m3LocalMatrix.GetPosition();

	// resetting values
	Vector2 v2Acceleration, v2Dampening, v2ForceSum = Vector2(0.0f, 0.0f);

	// use WASD keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_W))
		v2ForceSum.y += m_fMaxSpeed;
		
	if (input->isKeyDown(aie::INPUT_KEY_S))
		v2ForceSum.y -= m_fMaxSpeed;

	if (input->isKeyDown(aie::INPUT_KEY_A))
		v2ForceSum.x -= m_fMaxSpeed; 

	if (input->isKeyDown(aie::INPUT_KEY_D))
		v2ForceSum.x += m_fMaxSpeed;

	// Calculating velocity
	v2Acceleration.x = v2ForceSum.x / m_fMass;
	v2Acceleration.y = v2ForceSum.y / m_fMass;
	v2Dampening = (m_v2Velocity * m_fDrag) * -1.0f;
	m_v2Velocity += (v2Acceleration + v2Dampening) * deltaTime;

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

void Player::draw(aie::Renderer2D* pRenderer)
{
	// Drawing player
	pRenderer->drawSpriteTransformed3x3(
		nullptr, 
		(float*)m_m3GlobalMatrix, 
		50.0f, 
		50.0f
	);
	m_ShipTurret->Draw(pRenderer);
}

void Player::OnCollision(Actor* collidingObject, CollisionData* data)
{
}
