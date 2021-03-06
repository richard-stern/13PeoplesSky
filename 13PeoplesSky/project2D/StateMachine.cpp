#include "StateMachine.h"
#include "BaseState.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"

StateMachine::StateMachine()
{
	m_eCurrentState = ESTATE_MENU;

	// Create states in state array
	m_pStates[0] = new MenuState();
	m_pStates[1] = new GameState();
	m_pStates[2] = new GameOverState();

	// Enter first state
	m_pStates[0]->Enter();
}

StateMachine::~StateMachine()
{
	for (int i = 0; i < 3; ++i)
	{
		delete m_pStates[i];
	}
}

void StateMachine::ChangeState(ESTATE eState)
{
	m_pStates[m_eCurrentState]->Exit();
	m_eCurrentState = eState;
	m_pStates[m_eCurrentState]->Enter();
}

void StateMachine::Update(float fDeltaTime)
{
	m_pStates[m_eCurrentState]->Update(fDeltaTime, this);
}

void StateMachine::Draw(aie::Renderer2D* pRenderer)
{
	m_pStates[m_eCurrentState]->Draw(pRenderer);
}