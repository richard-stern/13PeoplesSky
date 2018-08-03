#pragma once
#include "Renderer2D.h"
#include "Vector2.h"

#define PLAYER_HEALTH     6
#define NO_SCORE		  0
#define NUMBER_OF_LIVES   3
#define NUMBER_OF_BULLETS 3

#define GUI_FONT_SIZE 24

#define HEALTH_BAR_OFFSET_X 80.0f
#define HEALTH_BAR_OFFSET_Y 40.0f

#define HEALTH_MODULE_WIDTH    12.0f
#define HEALTH_MODULE_HEIGHT   26.0f
#define HEALTH_MODULE_OFFSET_X 15.0f
#define HEALTH_MODULE_OFFSET_Y  4.0f

#define SCORE_OFFSET_X 160.0f
#define SCORE_OFFSET_Y 30.0f

#define AMMO_OFFSET_X 45.0f
#define AMMO_OFFSET_Y 80.0f

class GUI
{
private:
	GUI(); /* private constructor to restrict initialisation */
	~GUI(); /* destructor for memory deallocation */
	
	static GUI *instance; /* single instance of "this" */ 

	int maxHealth;
	int health;
	int score;
	int lives;
	int ammo;

public:
	static void Destroy();
	
	static GUI *GetInstance(); /* retrieve single instance of GUI class */

	void Reset(); /* Resets GUI to initialised values */
	
	void Draw(aie::Renderer2D *renderer); /* draw the UI */
	void DrawHealthBar(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position);
	void DrawScore(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position);
	void DrawAmmo(aie::Renderer2D *renderer, Vector2 resolution, Vector2 position);

	/* health getters/setters */
	void SetHealth(int health);
	int GetHealth();

	/* score getters/setters */
	void AddScore(int score); 
	int GetScore();

	/* lives getters/setters */
	void SetLives(int remainingLives); /* set the amount of player lives left */
	int GetLives();

	/* ammo getters/setters */
	void AddAmmo(int optionalQty = 1);
	void UseAmmo();
	void SetAmmo(int value);
	int GetAmmo();
};

