#pragma once
#include "BaseState.h"
#include "Matrix3.h"
#include "Texture.h"
class Camera;
class MenuState : public BaseState
{
public:
	MenuState();
	~MenuState();

	//----------------------------------------------
	// Enter
	//----------------------------------------------
	// Initialise state assets
	// Called when state starts
	// Basically a constructor for the class
	void Enter();

	//----------------------------------------------
	// Update
	//----------------------------------------------
	// Processes input
	// Updates assets
	// Changes StateMachine state when criteria is met
	// Called each frame
	void Update(float fDeltaTime, StateMachine* pStateMachine);

	//----------------------------------------------
	// Draw
	//----------------------------------------------
	// Draws each asset in state
	// Called each frame
	void Draw(aie::Renderer2D* pRenderer);

	//----------------------------------------------
	// Exit
	//----------------------------------------------
	// Deletes state assets
	// Called when state ends
	// Basically a destructor for the class
	void Exit();

private:
	Matrix3* m_m3StartButton;
	Matrix3* m_m3QuitButton;
	Matrix3* m_m3GameTitle;
	Matrix3* m_m3Explosion;

	aie::Texture* m_pStartTexture;
	aie::Texture* m_pQuitTexture;
	aie::Texture* m_pGameTitle;
	aie::Texture* m_pMenuBackground;
	aie::Texture* m_pExplosionTexture;

	Vector2* m_v2WindowSize;
	Vector2* m_v2ButtonSize;
	Vector2* m_v2TitleSize;

	bool m_bExiting;
	bool m_bStarting;
	float m_fScreenFade;

	bool m_bExploding;
	unsigned int m_nExplosionIterator;

	Camera* m_pCamera;
};