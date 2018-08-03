#include "GUI.h"
#include "Font.h"
#include "Texture.h"
#include "Camera.h"
#include "TextureManager.h"

GUI* GUI::instance = nullptr;

/*
Function:	 Constructor
Description: Memory allocation. Private to restrict initialisation of singleton class
*/
GUI::GUI()
{
	maxHealth = PLAYER_HEALTH;
	health = maxHealth;
	score = NO_SCORE;
	lives = NUMBER_OF_LIVES;
	ammo = 1;
}

/*
Function:	 Destructor
*/
GUI::~GUI()
{
}

/*
Function:	 GetInstance
Output:		 GUI*
Description: Retrieves singleton instance of graphical user interface class
*/
GUI* GUI::GetInstance()
{
	if (!instance)
	{
		instance = new GUI; /* initialise instance */
	}

	return instance;
}

/*
Function:	 Destroy
Description: Destructor which deallocates the graphical user interface singleton instance
*/
void GUI::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

/*
Function:	 Reset
Description: Resets GUI to initialised values
*/
void GUI::Reset()
{
	maxHealth = PLAYER_HEALTH;
	health = maxHealth;
	score = NO_SCORE;
	lives = NUMBER_OF_LIVES;
	ammo = 1;
}

/*
Function:	 Draw
Input/s:	 Renderer2D
Description: Draws the graphical user interface
*/
void GUI::Draw(aie::Renderer2D *renderer)
{
	Vector2 cameraResolution = Camera::GetInstance()->GetResolution();
	Vector2 cameraPosition = Camera::GetInstance()->GetPosition();

	/* health */
	/*float healthPosY = resolution.y - CORNER_OFFSET_Y;
	renderer->drawText(font, "Health", xPos, healthPosY);
	renderer->drawText(font, (char*)health, xPos + CORNER_OFFSET_X, healthPosY);*/
	DrawHealthBar(renderer, cameraResolution, cameraPosition);

	/* score */
	DrawScore(renderer, cameraResolution, cameraPosition);
}

/*
Function:	 DrawHealthBar
Input/s:	 Renderer2D, Vector2, Vector2
Description: Draw the player's health bar
*/
void GUI::DrawHealthBar(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position)
{
	/* HP bar texture */
	aie::Texture *healthBar = TextureManager::GetInstance()->LoadTexture("./textures/healthBar.png");
	float healthBarPosX = position.x + HEALTH_BAR_OFFSET_X; /* anchored to left of screen */
	float healthBarPosY = resolution.y + position.y - HEALTH_BAR_OFFSET_Y; /* anchored to top of screen */
	renderer->drawSprite(healthBar, healthBarPosX, healthBarPosY); /* draw HP bar */

	/* HP "modules" */
	float healthPercentage = (float)health / (float)maxHealth;
	renderer->setRenderColour(0x70DD54FF);

	for (int i = 0; i < health; i++)
	{
		float healthPosX = HEALTH_MODULE_OFFSET_X + healthBarPosX - (healthBar->getWidth() * 0.5f) + (20.0f * i);
		float healthPosY = HEALTH_MODULE_OFFSET_Y + healthBarPosY;

		switch (i)
		{
		case 4:
		{
			float uniqueModuleY = healthPosY + 2;
			float uniqueModuleHeight = HEALTH_MODULE_HEIGHT + 4;
			renderer->drawBox(healthPosX, uniqueModuleY, HEALTH_MODULE_WIDTH, uniqueModuleHeight);
			break;
		}
		case 5:
		{
			float uniqueModuleY = healthPosY + 4;
			float uniqueModuleHeight = HEALTH_MODULE_HEIGHT + 8;
			renderer->drawBox(healthPosX, uniqueModuleY, HEALTH_MODULE_WIDTH, uniqueModuleHeight);
			break;
		}
		default:
		{
			renderer->drawBox(healthPosX, healthPosY, HEALTH_MODULE_WIDTH, HEALTH_MODULE_HEIGHT);
			break;
		}
		}
	}

	renderer->setRenderColour(0x3B6CBBFF);

	for (int i = 0; i < lives; i++)
	{
		float lifeBallPosX = position.x + HEALTH_BAR_OFFSET_X + healthBar->getWidth() * 0.5f - 28.0f + 10.0f * (float)i;
		float lifeBallPosY = resolution.y + position.y - HEALTH_BAR_OFFSET_Y - 20.0f;

		renderer->drawCircle(lifeBallPosX, lifeBallPosY, 3.5f);
	}

	renderer->setRenderColour(0xFFFFFFFF);
}

/*
Function:	 DrawScore
Input/s:	 Renderer2D, Vector2, Vector2
Description: Draw the player's current score
*/
void GUI::DrawScore(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position)
{
	aie::Font *font = TextureManager::GetInstance()->LoadFont("./font/consolas_bold.ttf", GUI_FONT_SIZE);
	
	float scorePosX = position.x + SCORE_OFFSET_X;
	float scorePosY = resolution.y + position.y - SCORE_OFFSET_Y;
	//renderer->drawText(font, "Score: ", scorePosX, scorePosY); /* Score: */
	

	char scoreDisplay[8];
	sprintf(scoreDisplay, "%i", score);
	renderer->drawText(font, scoreDisplay, scorePosX, scorePosY);
}

/*
Function:	 DrawAmmo
Input/s:	 Renderer2D, Vector2, Vector2
Description: Draw the player's remaining ammo
*/
void GUI::DrawAmmo(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position)
{
	for (int i = 0; i < NUMBER_OF_BULLETS; i++)
	{
		aie::Texture *bullet = TextureManager::GetInstance()->LoadTexture("./textures/bulletUI.png");

		if (ammo < i)
		{
			renderer->setRenderColour(0x444444FF);
		}

		float ammoPosX = position.x + AMMO_OFFSET_X + i * 10.0f;
		float ammoPosY = resolution.y + position.y - AMMO_OFFSET_Y;
		renderer->setRenderColour(0xFFFFFFFF);
	}
}

/*
Function:	 SetHealth
Input/s:	 int
Description: Sets the health displayed on the UI
*/
void GUI::SetHealth(int newHealth)
{
	health = newHealth;
}

/*
Function:	 GetHealth
Output:		 int
Description: Retrieves the health displayed on the UI
*/
int GUI::GetHealth()
{
	return health;
}

/*
Function:	 AddScore
Input/s:	 int
Description: Increments the score displayed on the UI
*/
void GUI::AddScore(int value)
{
	score += value;
}

/*
Function:	 GetScore
Output:		 int
Description: Retrieves the score displayed on the UI
*/
int GUI::GetScore()
{
	return score;
}

/*
Function:	 SetLives
Input/s:	 int
Description: Set the number of lives displayed on the UI
*/
void GUI::SetLives(int remainingLives)
{
	lives = remainingLives;
}

/*
Function:	 GetLives
Output:		 int
Description: Retrieves the number of lives displayed on the UI
*/
int GUI::GetLives()
{
	return lives;
}

/*
Function:	 AddAmmo
Input/s:	 int
Description: Increments the GUI's ammo count by one unless fed optional argument
*/
void GUI::AddAmmo(int optionalQty)
{
	ammo += optionalQty;
}

/*
Function:	 UseAmmo
Description: Decrements the GUI's ammo by one
*/
void GUI::UseAmmo()
{
	ammo--;
}

/*
Function:	 GetAmmo
Output:		 int
Description: Retrieves the number of remaining ammo
*/
int GUI::GetAmmo()
{
	return ammo;
}