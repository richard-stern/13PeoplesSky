#pragma once
#include "Renderer2D.h"
class StateMachine;
class BaseState
{
public:
	BaseState();
	~BaseState();

	// Initialise state assets, called when state is started
	virtual void Enter() = 0;

	// Updates assets in state, called each frame
	virtual void Update(float fDeltaTime, StateMachine* pStateMachine) = 0;

	// Draws assets in state, called each frame
	virtual void Draw(aie::Renderer2D* pRenderer) = 0;

	// Delete all assets in state, called when state is exited
	virtual void Exit() = 0;
};