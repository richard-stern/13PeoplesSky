#pragma once

#include "BaseState.h"

class GameOverState : public BaseState
{
public:
	GameOverState();
	~GameOverState();

	void Enter() override;
	void Update(float fDeltaTime, StateMachine* pStateMachine);
	void Draw(aie::Renderer2D* pRenderer);
	void Exit();
};