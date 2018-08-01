#pragma once
#include "BaseState.h"


class Level;
class GameState : public BaseState
{
public:
	GameState();
	~GameState();
	void Enter();
	void Update(float fDeltaTime, StateMachine* pStateMachine);
	void Draw(aie::Renderer2D* pRenderer);
	void Exit();
private:
	Level* level;
};

