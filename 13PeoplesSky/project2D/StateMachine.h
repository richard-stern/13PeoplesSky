#pragma once
#include "Renderer2D.h"
class BaseState;
enum ESTATE
{
	ESTATE_MENU = 0,
	ESTATE_GAME,
	ESTATE_GAMEOVER
};

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	// Change game state
	void ChangeState(ESTATE eState);

	// Update current game state
	void Update(float fDeltaTime);

	// Draw current game state
	void Draw(aie::Renderer2D* pRenderer);

private:
	ESTATE m_eCurrentState;
	BaseState* m_pStates[3];
};