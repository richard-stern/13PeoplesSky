#pragma once
#include "BaseState.h"
class MenuState : public BaseState
{
public:
	MenuState();
	~MenuState();

	void Enter();
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void Exit();
};