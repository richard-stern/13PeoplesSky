#include "Rock.h"
#include "TextureManager.h"


Rock::Rock()
{
	//set health and max health
	m_nMaxHealth = 3;
	m_nHealth = 3;
	TextureManager* textureMan = TextureManager::GetInstance();
	//TEMP TEXTURE, replace when new texture made
	this->SetTexture(textureMan->LoadTexture("./textures/rock_large.png"));
}


Rock::~Rock()
{
}

void Rock::OnCollision(GameObject* collide)
{
}
