#pragma once

#include "Application.h"
#include "Renderer2D.h"

class StateMachine;
class Enemy;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	StateMachine * m_pStateMachine;

	aie::Renderer2D*	m_2dRenderer;

	float m_cameraX, m_cameraY;
	float m_timer;
};