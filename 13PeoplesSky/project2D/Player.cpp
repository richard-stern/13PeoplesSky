#include <Input.h>
#include "Player.h"
//#include "TextureManager.h"

Player::Player()
{
	// Requests a texture from TextureManager
	m_m3LocalMatrix.SetPosition(Vector2(600.0f, 600.0f));
	m_v2Velocity = Vector2(0.0f, 0.0f);
	m_fMaxSpeed = 100.0f;
	m_timer = 0.0f;
	m_fMass = 0.5f;
	m_fDrag = 0.5f;
}

Player::~Player()
{
	
}

void Player::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	Matrix3 mScale;
	Vector2 v2Pos = m_m3LocalMatrix.GetPosition();
	Vector2 v2Acceleration = Vector2(0.0f, 0.0f);
	Vector2 v2Dampening = Vector2(0.0f, 0.0f);
	Vector2 v2ForceSum = Vector2(0.0f, 0.0f);


	//Actor::update(deltaTime, 150.0f);
	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_W))
		v2ForceSum.y += m_fMaxSpeed;
		
	if (input->isKeyDown(aie::INPUT_KEY_S))
		v2ForceSum.y -= m_fMaxSpeed;

	if (input->isKeyDown(aie::INPUT_KEY_A))
		v2ForceSum.x -= m_fMaxSpeed; 

	if (input->isKeyDown(aie::INPUT_KEY_D))
		v2ForceSum.x += m_fMaxSpeed;

	v2Acceleration.x = v2ForceSum.x / m_fMass;
	v2Acceleration.y = v2ForceSum.y / m_fMass;
	v2Dampening = (m_v2Velocity * m_fDrag) * -1.0f;
	m_v2Velocity += (v2Acceleration + v2Dampening) * deltaTime;
	v2Pos = v2Pos + (m_v2Velocity * deltaTime);
	mPosition.SetPosition(v2Pos);
	m_m3LocalMatrix = mScale * mPosition;

	// update GlobalTransform
	//m_cLevelCamera.SetPosition();
}

void Player::draw(aie::Renderer2D* pRenderer)
{
	//insert GlobalTransform
	pRenderer->drawSpriteTransformed3x3(nullptr, (float*)m_m3LocalMatrix, 50.0f, 50.0f);
}

int Player::GetHealth(){ return 100; } //TODO Return Health
//void Player::SetCamera(Camera * LevelCamera){ m_cLevelCamera = LevelCamera; }
