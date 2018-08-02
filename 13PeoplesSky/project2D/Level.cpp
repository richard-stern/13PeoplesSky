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
			r->SetPosition(Vector2( j * 200, i * 200));
		}
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Enemy* e = new Enemy;
			this->AddChild(e);
			e->SetParent(this);
			e->SetPosition(Vector2(j * 175, i * 175));
		}
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			HealthPickup* h = new HealthPickup;
			this->AddChild(h);
			h->SetParent(this);
			h->SetPosition(Vector2(j * 225, i * 225));
		}
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Star* s = new Star;
			this->AddChild(s);
			s->SetParent(this);
			s->SetPosition(Vector2(j * 150, i * 150));
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