#pragma once
#include "Renderer2D.h"
class StateMachine;
class BaseState
{
public:
	BaseState();
	virtual ~BaseState();

	//----------------------------------------------
	// Enter
	//----------------------------------------------
	// Initialise state assets
	// Called when state starts
	// Basically a constructor for the class
	virtual void Enter() = 0;

	//----------------------------------------------
	// Update
	//----------------------------------------------
	// Processes input
	// Updates assets
	// Changes StateMachine state when criteria is met
	// Called each frame
	virtual void Update(float fDeltaTime, StateMachine* pStateMachine) = 0;

	//----------------------------------------------
	// Draw
	//----------------------------------------------
	// Draws each asset in state
	// Called each frame
	virtual void Draw(aie::Renderer2D* pRenderer) = 0;

	//----------------------------------------------
	// Exit
	//----------------------------------------------
	// Deletes state assets
	// Called when state ends
	// Basically a destructor for the class
	virtual void Exit() = 0;
};