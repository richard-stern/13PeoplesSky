#include "GameOverState.h"

#include <cassert>

#include "GUI.h"
#include "Camera.h"
#include "TextureManager.h"

GameOverState::GameOverState() 
{
	TextureManager* manager = TextureManager::GetInstance();
	assert(manager && "Texture manager should exist!");

	m_font = manager->LoadFont("./font/consolas.ttf", 16);
}

GameOverState::~GameOverState() { }

void GameOverState::Enter() 
{ 
	// grab the score from the GUI
	m_lastScore = GUI::GetInstance()->GetScore();
}

void GameOverState::Update(float fDeltaTime, StateMachine* pStateMachine) 
{
}

void GameOverState::Draw(aie::Renderer2D* pRenderer) 
{ 
	// grab the size of the window 
	Vector2 windowSize = Camera::GetInstance()->GetResolution();

	// make score text
	char scoreText[32];
	sprintf(scoreText, "Score: %i", m_lastScore);

	// grab the width of the string so we can center it
	float scoreWidth = m_font->getStringWidth(scoreText);
	// and store the center position here for cleanliness
	float centerPos = windowSize.x / 2.0f - scoreWidth / 2.0f;

	// print it somewhere in the middle of the screen
	pRenderer->setRenderColour(0xffffffff);
	pRenderer->drawText(m_font, scoreText, centerPos, 200.0f);
}

void GameOverState::Exit() { }
