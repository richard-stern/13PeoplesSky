#include "Star.h"
#include "TextureManager.h"

Star::Star()
{
	m_bVisible = true;
	m_bWrapAndRespawn = true;
	m_pTexture = TextureManager::GetInstance()->LoadTexture("./textures/star.png");		//loads texture from texture manager
} 

Star::~Star()
{
}

void Star::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix);
}