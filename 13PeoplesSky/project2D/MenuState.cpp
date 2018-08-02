#include "MenuState.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Vector2.h"
#include "Application2D.h"
#include "Camera.h"
MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::Enter()
{
	// Get camera instance
	m_pCamera = Camera::GetInstance();

	// Get window width/height
	m_v2WindowSize = new Vector2();
	m_v2ButtonSize = new Vector2();
	m_v2TitleSize = new Vector2();
	*m_v2WindowSize = m_pCamera->GetResolution();

	// Get button and title size
	*m_v2ButtonSize = Vector2(m_v2WindowSize->x * 0.45f, m_v2WindowSize->y * 0.2f);
	*m_v2TitleSize = Vector2(m_v2WindowSize->x * 0.8f, m_v2WindowSize->y * 0.2f);

	// Allocate button matrices
	m_m3StartButton = new Matrix3();
	m_m3QuitButton = new Matrix3();
	m_m3GameTitle = new Matrix3();

	// Find centre of window on x axis
	unsigned int nWindowMiddleX = (unsigned int)m_v2WindowSize->x / 2;

	// Set button positions
	m_m3StartButton->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.5f);
	m_m3QuitButton->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.2f);
	m_m3GameTitle->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.8f);

	// Load button textures
	TextureManager* textureMan = TextureManager::GetInstance();
	m_pStartTexture = textureMan->LoadTexture("./textures/startButton.png");
	m_pQuitTexture = textureMan->LoadTexture("./textures/quitButton.png");
	m_pGameTitle = textureMan->LoadTexture("./textures/gameTitle.png");
	m_pMenuBackground = textureMan->LoadTexture("./textures/menuBackground.png");
}

void MenuState::Update(float fDeltaTime, StateMachine* pStateMachine)
{
	// Get resolution each frame (in case of window resize)
	m_pCamera = Camera::GetInstance();
	*m_v2WindowSize = m_pCamera->GetResolution();

	unsigned int nWindowMiddleX = (unsigned int)m_v2WindowSize->x / 2;

	// Get button size and title size based on window resolution
	*m_v2ButtonSize = Vector2(m_v2WindowSize->x * 0.45f, m_v2WindowSize->y * 0.2f);
	*m_v2TitleSize = Vector2(m_v2WindowSize->x * 0.8f, m_v2WindowSize->y * 0.2f);

	// Set button positions based on window resolution (in case of window resize)
	m_m3StartButton->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.5f);
	m_m3QuitButton->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.2f);
	m_m3GameTitle->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.8f);

	// Get input instance
	aie::Input* pInput = aie::Input::getInstance();

	if (pInput->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		// Store mouse position in Vector2
		Vector2 v2MousePos = Vector2((float)pInput->getMouseX(), (float)pInput->getMouseY());

		// Store button positions in Vector2
		Vector2 v2StartButtonPosition = m_m3StartButton->GetPosition();
		Vector2 v2QuitButtonPosition = m_m3QuitButton->GetPosition();

		Vector2 v2HalfButtonSize = *m_v2ButtonSize * 0.5;

		// Find if mouse is over start or quit button
		if (v2MousePos > Vector2(v2StartButtonPosition.x - v2HalfButtonSize.x, v2StartButtonPosition.y - v2HalfButtonSize.y) && v2MousePos < Vector2(v2StartButtonPosition.x + v2HalfButtonSize.x, v2StartButtonPosition.y + v2HalfButtonSize.y))
		{
			// Enter game state
			pStateMachine->ChangeState(ESTATE_GAME);
		}
		else if (v2MousePos > Vector2(v2QuitButtonPosition.x - v2HalfButtonSize.x, v2QuitButtonPosition.y - v2HalfButtonSize.y) && v2MousePos < Vector2(v2QuitButtonPosition.x + v2HalfButtonSize.x, v2QuitButtonPosition.y + v2HalfButtonSize.y))
		{
			// Quit application
			Application2D::quit();
		}
	}
}

void MenuState::Draw(aie::Renderer2D* pRenderer)
{
	// Draw start button
	pRenderer->drawSpriteTransformed3x3(m_pStartTexture, (float*)m_m3StartButton, m_v2ButtonSize->x, m_v2ButtonSize->y);
	
	// Draw quit button
	pRenderer->drawSpriteTransformed3x3(m_pQuitTexture, (float*)m_m3QuitButton, m_v2ButtonSize->x, m_v2ButtonSize->y);

	// Draw game title
	pRenderer->drawSpriteTransformed3x3(m_pGameTitle, (float*)m_m3GameTitle, m_v2TitleSize->x, m_v2TitleSize->y);

	// Draw menu background
	pRenderer->drawSprite(m_pMenuBackground, 0.0f, 0.0f, m_v2WindowSize->x, m_v2WindowSize->y , 0.0f, 100.0f, 0.0f, 0.0f);
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

	delete m_v2WindowSize;
	m_v2WindowSize = nullptr;

	delete m_v2ButtonSize;
	m_v2ButtonSize = nullptr;

	delete m_v2TitleSize;
	m_v2TitleSize = nullptr;
}