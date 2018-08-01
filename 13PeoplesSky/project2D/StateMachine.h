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

	//----------------------------------------------
	// ChangeState
	//----------------------------------------------
	// Used to switch between states
	//	Process:
	//	1.	Exit current state
	//	2.	Set current state as parameter
	//	3.	Enter new current state
	void ChangeState(ESTATE eState);

	//----------------------------------------------
	// Update
	//----------------------------------------------
	// Calls the update function of the current state
	// Passes fDeltaTime and this pointer into current state
	// Called every frame
	void Update(float fDeltaTime);

	//----------------------------------------------
	// Draw
	//----------------------------------------------
	// Calls the draw function of the current state
	// Passes Renderer2D pointer into current state
	// Called every frame
	void Draw(aie::Renderer2D* pRenderer);

private:
	// Stores current state
	ESTATE m_eCurrentState;

	// Stores array of all states
	BaseState* m_pStates[3];
};