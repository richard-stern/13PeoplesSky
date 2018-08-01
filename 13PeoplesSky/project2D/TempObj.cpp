#include "TempObj.h"
#include "Primatives.h"
#include "Input.h"

TempObj::TempObj(aie::Texture* pTex, Vector2 v2Pos)
{
	m_pTexture = pTex;

	m_m3LocalMatrix.SetPosition(v2Pos);

	m_collider = new PrimRectangle(64, 64);
}

TempObj::~TempObj()
{
	delete m_pTexture;
	delete m_collider;
}

void TempObj::Update(float fDeltaTime) 
{
	aie::Input* input = aie::Input::getInstance();

	if(input->isKeyDown(aie::INPUT_KEY_W)) 
	{
		m_m3LocalMatrix.SetPosition(m_m3GlobalMatrix.GetPosition() + Vector2(0, SPEED * fDeltaTime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		m_m3LocalMatrix.SetPosition(m_m3GlobalMatrix.GetPosition() + Vector2(-SPEED * fDeltaTime, 0));
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		m_m3LocalMatrix.SetPosition(m_m3GlobalMatrix.GetPosition() + Vector2(0, -SPEED * fDeltaTime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		m_m3LocalMatrix.SetPosition(m_m3GlobalMatrix.GetPosition() + Vector2(SPEED * fDeltaTime, 0));
	}

	if (input->isKeyDown(aie::INPUT_KEY_R))
	{
		m_fRotation = m_fRotation + (3.14f / 2) * fDeltaTime;
		m_m3LocalMatrix.SetRotate2D(m_fRotation);
	}
}

void TempObj::UpdateTransform() 
{
	m_m3GlobalMatrix = m_m3LocalMatrix;

	m_collider->UpdateBounds(&m_m3LocalMatrix);
}

void TempObj::Draw(aie::Renderer2D* pRenderer) 
{
	pRenderer->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix);

	m_collider->DrawCollider(m_m3GlobalMatrix.GetPosition() ,pRenderer);
}
