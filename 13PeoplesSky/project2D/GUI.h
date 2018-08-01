#pragma once
#include "Renderer2D.h"
#include "Font.h"

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
	static GUI *GetInstance(); /* retrieve single instance of GUI class */
	static void Destroy(); 

	void Draw(aie::Renderer2D *renderer); /* draw the UI */

	void SetHealth(int health); /* tell UI how much health to display */
	void AddScore(int score); /* tell UI to increase player score */
	int GetScore(); /* retrieve final score */
	void SetLives(int remainingLives); /* set the amount of player lives left */
};

