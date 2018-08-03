#pragma once
#include "GameObject.h"
#define STAR_COUNT 30
#define HEALTH_PICKUP_COUNT 1 
#define ROCK_COUNT 4
#define ENEMY_COUNT 3


class Rock; 
class Enemy;
class Player;

class Level : public GameObject
{
public:
	Level();
	~Level();
	void Draw(aie::Renderer2D* _render);
	void Update(float _delta_time);
	Rock** GetRocks();
	Enemy** GetEnemies();
	Player* GetPlayer();
private:
	Rock* rockID[ROCK_COUNT * ROCK_COUNT];
	Enemy* enemyID[ENEMY_COUNT * ENEMY_COUNT];
	Player* playerID;
	
};

