#include "GUI.h"

GUI* GUI::instance = nullptr;

/*
Function:	 Constructor
Description: Memory allocation. Private to restrict initialisation of singleton class
*/
GUI::GUI()
{
	health = 0;
	score = 0;
	lives = 0;

	instance = new GUI; /* initialise instance */
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
		GUI();
	}

	return instance;
}

/*
Function:	 Destroy
Description: Destructor which deallocates the graphical user interface singleton instance
*/
void GUI::Destroy()
{
	delete instance;
	instance = nullptr;
}

/*
Function:	 Draw
Input/s:	 Renderer2D
Description: Draws the graphical user interface
*/
void GUI::Draw(aie::Renderer2D *renderer)
{
	Vector2 resolution = Camera::GetInstance()->GetResolution();
	aie::Font *font = TextureManager::GetInstance()->LoadFont("./font/consolas_bold.ttf", GUI_FONT_SIZE);
	float xPos = CORNER_OFFSET_X;

	/* health */
	float healthPosY = resolution.y - CORNER_OFFSET_Y;
	
	renderer->drawText(font, "Health", xPos, healthPosY);
	renderer->drawText(font, (char*)health, xPos + CORNER_OFFSET_X, healthPosY);

	/* score */
	float scorePosY = resolution.y - 2 * CORNER_OFFSET_Y;

	renderer->drawText(font, "Score", xPos, scorePosY);
	renderer->drawText(font, (char*)score, xPos + CORNER_OFFSET_X, scorePosY);

	/* lives */
	//float livesPosX, livesPosY;
	//renderer->drawText(font, lives, xPos, yPos);
}

/*
Function:	 SetHealth
Input/s:	 int
Description: Sets 
*/
void GUI::SetHealth(int newHealth)
{
	health = newHealth;
}

/*
Function:	 AddScore
Input/s:	 int
Description: 
*/
void GUI::AddScore(int value)
{
	score += value;
}

/*
Function:	 GetScore
Output:		 int
Description: 
*/
int GUI::GetScore()
{
	return score;
}

/*
Function:	 SetLives
Input/s:	 int
Description: 
*/
void GUI::SetLives(int remainingLives)
{
	lives = remainingLives;
}