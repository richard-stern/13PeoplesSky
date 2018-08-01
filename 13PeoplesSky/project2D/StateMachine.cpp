#include "StateMachine.h"
#include "BaseState.h"

StateMachine::StateMachine()
{
	m_eCurrentState = ESTATE_MENU;

	// Create states in state array
	
}

StateMachine::~StateMachine()
{
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