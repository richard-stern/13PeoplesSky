#pragma once
#include "BaseState.h"
class GameState : BaseState
{
public:
	GameState();
	~GameState();
	void Enter();
	void Update(float fDeltaTime, StateMachine* pStateMachine);
	void Draw(aie::Renderer2D* pRenderer);
	void Exit();
};

