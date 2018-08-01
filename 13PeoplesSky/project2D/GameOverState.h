#pragma once

#include "BaseState.h"

class GameOverState :
	public BaseState
{
public:
	GameOverState();
	~GameOverState();

	void Enter() override;
	void Update(float fDeltaTime, StateMachine* pStateMachine) override;
	void Draw(aie::Renderer2D* pRenderer) override;
	void Exit() override;
};

