#pragma once
#include "Matrix3.h"
#include "Texture.h"
#include "Renderer2D.h"
#include "Vector2.h"

class Collider;

#define SPEED 500

class TempObj
{
public:

	TempObj(aie::Texture* pTex, Vector2 v2Pos = Vector2(0, 0));

	~TempObj();

	void Update(float fDeltaTime);

	void UpdateTransform();

	void Draw(aie::Renderer2D* pRenderer);

private:

	aie::Texture* m_pTexture;
	Matrix3 m_m3LocalMatrix;
	Matrix3 m_m3GlobalMatrix;

	Collider* m_collider;

	float m_fRotation = 0.0f;
};

