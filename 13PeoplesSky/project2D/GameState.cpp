#include "GameState.h"
#include "GUI.h"
#include "Level.h"
#include "CollisionManager.h"
#include "StateMachine.h"
#include "Camera.h"
GameState::GameState()
{
	level = nullptr;
}

GameState::~GameState()
{
	GUI::Destroy();

	if (level)
	{
		delete level;
		level = nullptr;
	}
}

void GameState::Enter()
{
	GUI::GetInstance()->Reset();
	CollisionManager::GetInstance()->Clear();
	level = new Level;
}

void GameState::Update(float fDeltaTime, StateMachine* pStateMachine)
{
	level->Update(fDeltaTime);
	CollisionManager::GetInstance()->Update();
	Camera::GetInstance()->Update(fDeltaTime);
	auto gui = GUI::GetInstance();

	int health = gui->GetHealth();
	int lives = gui->GetLives();

	if (health <= 0)
	{
		lives--;
		if (lives <= 0)
		{
			pStateMachine->ChangeState(ESTATE_GAMEOVER);
			return;
		}

		gui->SetLives(lives);
		gui->SetAmmo(1);

		// RESET level ... poor mans way
		CollisionManager::GetInstance()->Clear();
		delete level;
		level = new Level;

	}
}

void GameState::Draw(aie::Renderer2D* pRenderer)
{
	level->Draw(pRenderer);
	GUI::GetInstance()->Draw(pRenderer);
}

void GameState::Exit()
{
	if (level)
	{
		delete level;
		level = nullptr;
    }
}

