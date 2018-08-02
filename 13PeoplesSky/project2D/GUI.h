#pragma once
#include "Renderer2D.h"

#define GUI_FONT_SIZE 24
#define CORNER_OFFSET_X 40.0f
#define CORNER_OFFSET_Y 20.0f

class GUI
{
private:
	GUI(); /* private constructor to restrict initialisation */
	~GUI(); /* destructor for memory deallocation */
	
	static GUI *instance; /* single instance of "this" */

	int health;
	int score;
	int lives;

public:
	static void Destroy();
	
	static GUI *GetInstance(); /* retrieve single instance of GUI class */
	
	void Draw(aie::Renderer2D *renderer); /* draw the UI */
	void DrawHealthBar(aie::Renderer2D *renderer);
	void DrawScore(aie::Renderer2D *renderer);
	void DrawLives(aie::Renderer2D *renderer);

	void SetHealth(int health); /* tell UI how much health to display */
	void AddScore(int score); /* tell UI to increase player score */
	int  GetScore(); /* retrieve final score */
	void SetLives(int remainingLives); /* set the amount of player lives left */
};

