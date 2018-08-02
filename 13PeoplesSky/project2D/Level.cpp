#include "Level.h"
#include "Player.h"
#include "Rock.h"
#include "Enemy.h"
#include "HealthPickup.h"
#include "Star.h"

Level::Level()
{
	m_bWrapAndRespawn = false;

	Player* p = new Player;
	this->AddChild(p);
	p->SetParent(this);
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Rock* r = new Rock;
			this->AddChild(r);
			r->SetParent(this);
			int randX = rand() % 200;
			int randY = rand() % 200;
			r->SetPosition(Vector2( j * 400.0f + randX, i * 400.0f + randY));
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Enemy* e = new Enemy;
			this->AddChild(e);
			e->SetParent(this);
			int randX = rand() % 1100;
			int randY = rand() % 1100;
			e->SetPosition(Vector2(j * 415.0f + randX, i * 445.0f + randY));
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			HealthPickup* h = new HealthPickup;
			this->AddChild(h);
			h->SetParent(this);
			int randX = rand() % 1300;
			int randY = rand() % 1300;
			h->SetPosition(Vector2(j * 425.0f + randX, i * 475.0f + randY));
		}
	}
	
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1 ; j++)
		{
			Star* s = new Star;
			this->AddChild(s);
			s->SetParent(this);
			int randX = rand() % 2000;
			int randY = rand() % 2000;
			s->SetPosition(Vector2(j * 475.0f + randX, i * 450.0f + randY));
		}
	}

}

Level::~Level()
{
	for (auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
	{
		delete (*iter);
	}
	
}

void Level::Draw(aie::Renderer2D* _render)
{
	GameObject::Draw(_render);
}
void Level::Update(float _delta_time)
{
	GameObject::Update(_delta_time);
}