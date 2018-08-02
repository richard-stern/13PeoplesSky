#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "CollisionManager.h"

Application2D::Application2D() {
	
}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	float resX, resY;
	resX = (float)getWindowWidth();
	resY = (float)getWindowHeight();
	Camera::GetInstance()->SetResolution(Vector2(resX, resY));

	TextureManager::Create();
	CollisionManager::CreateInstance();

	m_pStateMachine = new StateMachine();
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;


	return true;
}

void Application2D::shutdown() {
	
	delete m_pStateMachine;

	Camera::Destroy();
	TextureManager::Destroy();
	CollisionManager::DestroyInstance();

	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	// input
	aie::Input* input = aie::Input::getInstance();

	float resX, resY;
	resX = (float)getWindowWidth();
	resY = (float)getWindowHeight();
	Camera::GetInstance()->SetResolution(Vector2(resX, resY));

	m_pStateMachine->Update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	Vector2 cameraPos = Camera::GetInstance()->GetPosition();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(cameraPos.x, cameraPos.y);

	// begin drawing sprites
	m_2dRenderer->begin();

	m_pStateMachine->Draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}