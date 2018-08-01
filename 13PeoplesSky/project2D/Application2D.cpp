#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D() {
	
}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	obj = new TempObj(new aie::Texture("./textures/ship.png"), Vector2(300.0f, 300.0f));

	return true;
}

void Application2D::shutdown() {
	
	delete obj;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	// input
	aie::Input* input = aie::Input::getInstance();

	obj->Update(deltaTime);
	obj->UpdateTransform();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	obj->Draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}