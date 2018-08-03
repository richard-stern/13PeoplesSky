#include "Level.h"
#include "Player.h"
#include "Rock.h"
#include "Enemy.h"
#include "HealthPickup.h"
#include "Star.h"
#include "AmmoPickup.h"
#include "Explosion.h"

Level::Level()
{
	m_bWrapAndRespawn = false;

	for (int i = 0; i < STAR_COUNT; i++)
	{
		for (int j = 0; j < STAR_COUNT; j++) 
		{
			Star* s = new Star;
			this->AddChild(s); 
			s->SetParent(this);
			int randX = rand() % 50;
			int randY = rand() % 50;
			s->SetPosition(Vector2(j * 100.0f + randX, i * 100.0f + randY));
			//s->SetScale(Vector2((float)((rand() % 10) / 10), (float)((rand() % 10) / 10)));
			float scale = ((float)((rand() % 2) - 1)) / 10;
			s->SetScale(Vector2(scale, scale));

		}
	}

	for (int i = 0; i < ROCK_COUNT; i++)
	{
		for (int j = 0; j < ROCK_COUNT; j++)
		{
			Explosion* rockExplosion = new Explosion;
			rockExplosion->SetVisible(false);
			this->AddChild(rockExplosion);
			rockExplosion->SetParent(this);

			Rock* r = new Rock;
			this->AddChild(r);
			r->SetParent(this);
			r->SetExplosion(rockExplosion);
			int randX = rand() % 200;
			int randY = rand() % 200;
			r->SetPosition(Vector2( j * 400.0f + randX, i * 400.0f + randY));
			rockID[4 * i + j] = r;
		}
	}

	for (int i = 0; i < HEALTH_PICKUP_COUNT; i++)
	{
		for (int j = 0; j < HEALTH_PICKUP_COUNT; j++)
		{
			HealthPickup* h = new HealthPickup;
			this->AddChild(h);
			h->SetParent(this);
			int randX = rand() % 1300;
			int randY = rand() % 1300;
			h->SetPosition(Vector2(j * 425.0f + randX, i * 475.0f + randY));
		}
	}

	for (int i = 0; i < AMMO_COUNT; i++)
	{
		for (int j = 0; j < AMMO_COUNT; j++)
		{
			AmmoPickup* h = new AmmoPickup;
			this->AddChild(h);
			h->SetParent(this);
			int randX = rand() % 1300;
			int randY = rand() % 1300;
			h->SetPosition(Vector2(j * 425.0f + randX, i * 475.0f + randY));
		}
	}

	playerID = new Player;

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		for (int j = 0; j < ENEMY_COUNT; j++)
		{
			Explosion* enemyExplosion = new Explosion;
			enemyExplosion->SetVisible(false);
			this->AddChild(enemyExplosion);
			enemyExplosion->SetParent(this);

			Enemy* e = new Enemy(this);
			this->AddChild(e);
			enemyID[3 * i + j] = e;
			e->SetParent(this);
			e->SetExplosion(enemyExplosion);
			int randX = rand() % 1100;
			int randY = rand() % 1100;
			e->SetPosition(Vector2(j * 415.0f + randX, i * 445.0f + randY));

		}
	}

	this->AddChild(playerID);
	playerID->SetParent(this);
	
}

Level::~Level()
{
	for (auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
	{
		delete (*iter);
	}
	
}

Rock** Level::GetRocks()
{
	return rockID;
}

Enemy** Level::GetEnemies()
{
	return enemyID;
}

Player* Level::GetPlayer()
{
	return playerID;
}

void Level::Draw(aie::Renderer2D* _render)
{
	GameObject::Draw(_render);
}
void Level::Update(float _delta_time)
{
	GameObject::Update(_delta_time);
}