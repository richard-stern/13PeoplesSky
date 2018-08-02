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
	health = 10;
	score = 0;
	lives = 0;
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

	/* lives */
	/*float livesPosY = resolution.y - 3 * CORNER_OFFSET_Y;
	renderer->drawText(font, "Lives", xPos, livesPosY);
	renderer->drawText(font, (char*)lives, xPos + CORNER_OFFSET_X, scorePosY);*/
	//DrawLives(renderer);
}

/*
Function:	 DrawHealthBar
Input/s:	 Renderer2D
Description: Draw the player's health bar
*/
void GUI::DrawHealthBar(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position)
{
	aie::Texture *healthBar = TextureManager::GetInstance()->LoadTexture("./textures/healthBar.png");

	float healthPosX = position.x + CORNER_OFFSET_X;
	float healthPosY = resolution.y + position.y - CORNER_OFFSET_Y;
	float healthWidth = health * 5.6f;

	renderer->drawSprite(healthBar, healthPosX, healthPosY);
	renderer->setRenderColour(0x70DD54FF);
	renderer->drawBox(healthPosX, healthPosY, healthWidth, 12);
	renderer->setRenderColour(0xFFFFFFFF);
}

/*
Function:	 DrawScore
Input/s:	 Renderer2D
Description: Draw the player's current score
*/
void GUI::DrawScore(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position)
{
	aie::Font *font = TextureManager::GetInstance()->LoadFont("./font/consolas_bold.ttf", GUI_FONT_SIZE);
	
	float scorePosX = position.x + 8.0f;
	float scorePosY = resolution.y + position.y - 2.5f * CORNER_OFFSET_Y;
	
	renderer->drawText(font, "Score: ", scorePosX, scorePosY); /* Score: */

	char scoreDisplay[8];
	sprintf(scoreDisplay, "%i", score);
	renderer->drawText(font, scoreDisplay, scorePosX + 100.0f, scorePosY);
}

/*
Function:	 DrawLives
Input/s:	 Renderer2D
Description: Draw the player's number of remaining lives
*/
void GUI::DrawLives(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position)
{

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