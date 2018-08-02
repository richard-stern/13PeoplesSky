#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Vector2.h"

Application2D::Application2D() {
	
}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	Camera::GetInstance();
	TextureManager::Create();
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;


	return true;
}

void Application2D::shutdown() {
	
	Camera::Destroy();
	TextureManager::Destroy();

	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	// input
	aie::Input* input = aie::Input::getInstance();

	float resX, resY;
	resX = (float)getWindowWidth();
	resY = (float)getWindowHeight();

	Camera::GetInstance()->SetResolution(Vector2(resX, resY));

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


	// done drawing sprites
	m_2dRenderer->end();
}