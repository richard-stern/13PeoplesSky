#include "MenuState.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Vector2.h"
MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::Enter()
{
	// EVERYTHING HERE IS PLACEHOLDER

	// Allocate button matrices
	m_m3StartButton = new Matrix3();
	m_m3QuitButton = new Matrix3();
	m_m3GameTitle = new Matrix3();

	// Set button positions
	m_m3StartButton->SetPosition(640, 400);
	m_m3QuitButton->SetPosition(640, 200);
	m_m3GameTitle->SetPosition(640, 600);

	// Load button textures
	TextureManager* textureMan = TextureManager::GetInstance();
	m_pStartTexture = textureMan->LoadTexture("./textures/rock_large.png");
	m_pQuitTexture = textureMan->LoadTexture("./textures/rock_medium.png");
	m_pGameTitle = textureMan->LoadTexture("./textures/car.png");
}

void MenuState::Update(float fDeltaTime, StateMachine* pStateMachine)
{
	// Get input instance
	aie::Input* pInput = aie::Input::getInstance();

	if (pInput->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		// Store mouse position in Vector2
		Vector2 v2MousePos = Vector2(pInput->getMouseX(), pInput->getMouseY());

		// USE MOUSE POS TO FIND IF OVER BUTTON

	}
}

void MenuState::Draw(aie::Renderer2D* pRenderer)
{
	// Draw start button
	pRenderer->drawSpriteTransformed3x3(m_pStartTexture, (float*)m_m3StartButton);
	
	// Draw quit button
	pRenderer->drawSpriteTransformed3x3(m_pQuitTexture, (float*)m_m3QuitButton);

	// Draw game title
	pRenderer->drawSpriteTransformed3x3(m_pGameTitle, (float*)m_m3GameTitle);
}

void MenuState::Exit()
{
	// Delete assets
	delete m_m3StartButton;
	m_m3StartButton = nullptr;

	delete m_m3QuitButton;
	m_m3QuitButton = nullptr;

	delete m_m3GameTitle;
	m_m3GameTitle = nullptr;
}