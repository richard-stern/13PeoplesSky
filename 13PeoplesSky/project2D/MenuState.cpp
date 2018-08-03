#include "MenuState.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Vector2.h"
#include "Application2D.h"
#include "Camera.h"
#define SCREEN_FADE_SPEED 0.04f

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

	m_bExiting = false;
	m_bStarting = false;
	m_bExploding = false;
	m_fScreenFade = 0.0f;
	m_nExplosionIterator = 0;

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
	m_m3Explosion = new Matrix3();

	// Find centre of window on x axis
	unsigned int nWindowMiddleX = (unsigned int)m_v2WindowSize->x / 2;

	// Set button positions
	m_m3StartButton->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.5f);
	m_m3QuitButton->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.2f);
	m_m3GameTitle->SetPosition((float)nWindowMiddleX, m_v2WindowSize->y * 0.8f);

	// Load button textures
	TextureManager* textureMan = TextureManager::GetInstance();
	m_pStartTexture = textureMan->LoadTexture("./textures/startButton_duck.png");
	m_pQuitTexture = textureMan->LoadTexture("./textures/quitButton_duck.png");
	m_pGameTitle = textureMan->LoadTexture("./textures/gameTitle.png");
	m_pMenuBackground = textureMan->LoadTexture("./textures/menuBackground.png");
	m_pExplosionTexture = textureMan->LoadTexture("./textures/explosion_sheet.png");
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

	// Store mouse position in Vector2
	Vector2 v2MousePos = Vector2((float)pInput->getMouseX(), (float)pInput->getMouseY());

	// Store button positions in Vector2
	Vector2 v2StartButtonPosition = m_m3StartButton->GetPosition();
	Vector2 v2QuitButtonPosition = m_m3QuitButton->GetPosition();

	Vector2 v2HalfButtonSize = *m_v2ButtonSize * 0.5;

	if (v2MousePos > Vector2(v2StartButtonPosition.x - v2HalfButtonSize.x, v2StartButtonPosition.y - v2HalfButtonSize.y) && v2MousePos < Vector2(v2StartButtonPosition.x + v2HalfButtonSize.x, v2StartButtonPosition.y + v2HalfButtonSize.y))
	{
		m_m3StartButton->SetPosition(m_m3StartButton->m1[6] + rand() % 30 - 15, m_m3StartButton->m1[7] + rand() % 30 - 15);
	}
	else if (v2MousePos > Vector2(v2QuitButtonPosition.x - v2HalfButtonSize.x, v2QuitButtonPosition.y - v2HalfButtonSize.y) && v2MousePos < Vector2(v2QuitButtonPosition.x + v2HalfButtonSize.x, v2QuitButtonPosition.y + v2HalfButtonSize.y))
	{
		m_m3QuitButton->SetPosition(m_m3QuitButton->m1[6] + rand() % 30 - 15, m_m3QuitButton->m1[7] + rand() % 30 - 15);
	}

	// If left mouse button was clicked, find which button the mouse was over (if any)
	if (pInput->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		// Find if mouse is over start or quit button
		if (v2MousePos > Vector2(v2StartButtonPosition.x - v2HalfButtonSize.x, v2StartButtonPosition.y - v2HalfButtonSize.y) && v2MousePos < Vector2(v2StartButtonPosition.x + v2HalfButtonSize.x, v2StartButtonPosition.y + v2HalfButtonSize.y))
		{
			// Make screen fade out
			m_bStarting = true;

			if (!m_bExploding)
				m_m3Explosion->SetPosition(v2MousePos);
			m_bExploding = true;
		}
		else if (v2MousePos > Vector2(v2QuitButtonPosition.x - v2HalfButtonSize.x, v2QuitButtonPosition.y - v2HalfButtonSize.y) && v2MousePos < Vector2(v2QuitButtonPosition.x + v2HalfButtonSize.x, v2QuitButtonPosition.y + v2HalfButtonSize.y))
		{
			// Quit application
			Exit();
			Application2D::quit();
		}
	}

	// Exit state when press escape (application already exits, this fixes memory leaks)
	if (pInput->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		Exit();
	}

	// If the start button has been clicked
	if (m_bStarting)
	{
		// Increment screen fade
		m_fScreenFade += SCREEN_FADE_SPEED;

		m_nExplosionIterator++;

		// Start game if screen is black
		if (m_fScreenFade >= 1.0f)
			pStateMachine->ChangeState(ESTATE_GAME);
	}
}

void MenuState::Draw(aie::Renderer2D* pRenderer)
{
	// Don't try to draw if menu is exiting
	if (!m_bExiting)
	{
		// Draw start button
		pRenderer->drawSpriteTransformed3x3(m_pStartTexture, (float*)m_m3StartButton, m_v2ButtonSize->x, m_v2ButtonSize->y);

		// Draw quit button
		pRenderer->drawSpriteTransformed3x3(m_pQuitTexture, (float*)m_m3QuitButton, m_v2ButtonSize->x, m_v2ButtonSize->y);

		// Draw game title
		pRenderer->drawSpriteTransformed3x3(m_pGameTitle, (float*)m_m3GameTitle, m_v2TitleSize->x, m_v2TitleSize->y);

		// Draw menu background
		pRenderer->drawSprite(m_pMenuBackground, 0.0f, 0.0f, m_v2WindowSize->x, m_v2WindowSize->y, 0.0f, 100.0f, 0.0f, 0.0f);

		if (m_bExploding)
		{
			pRenderer->setUVRect(m_nExplosionIterator % 48 / 48.0f, m_nExplosionIterator, 1.0f / 48, 1.0f);
			pRenderer->drawSpriteTransformed3x3(m_pExplosionTexture, (float*)m_m3Explosion, 256, 256);
			pRenderer->setUVRect(0, 0, 1, 1);
		}

		// Draw screen fade
		pRenderer->setRenderColour(0, 0, 0, m_fScreenFade);
		pRenderer->drawBox(m_v2WindowSize->x * 0.5f, m_v2WindowSize->y * 0.5f, m_v2WindowSize->x, m_v2WindowSize->y);
		pRenderer->setRenderColour(1, 1, 1);
	}
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

	delete m_m3Explosion;
	m_m3Explosion = nullptr;

	delete m_v2WindowSize;
	m_v2WindowSize = nullptr;

	delete m_v2ButtonSize;
	m_v2ButtonSize = nullptr;

	delete m_v2TitleSize;
	m_v2TitleSize = nullptr;

	m_bExiting = true;
}