#include "GameState.h"
#include "GUI.h"
#include "Level.h"

GameState::GameState()
{
	
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
	level = new Level;
	GUI::GetInstance();
}

void GameState::Update(float fDeltaTime, StateMachine* pStateMachine)
{
	level->Update(fDeltaTime);

}

void GameState::Draw(aie::Renderer2D* pRenderer)
{
	level->Draw(pRenderer);
	GUI::GetInstance()->Draw(pRenderer);
}

void GameState::Exit()
{
	GUI::Destroy();

	if (level)
	{
		delete level;
		level = nullptr;
    }
}

