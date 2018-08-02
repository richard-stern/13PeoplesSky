#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "CollisionManager.h"

#include <imgui.h>

Application2D::Application2D() 
{
	
}

Application2D::~Application2D() 
{

}

bool Application2D::startup() 
{
	// Create Renderer
	m_2dRenderer = new aie::Renderer2D();

	// Set Camera Resolution and Create Camera
	float resX, resY;
	resX = (float)getWindowWidth();
	resY = (float)getWindowHeight();
	Camera::GetInstance()->SetResolution(Vector2(resX, resY));

	// Create Texture Manager
	TextureManager::Create();

	// Create Collider Manager
	CollisionManager::CreateInstance();

	// Create StateMachine
	m_pStateMachine = new StateMachine();
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;


	return true;
}

void Application2D::shutdown() 
{
	// delete StateMachine
	delete m_pStateMachine;

	// Destroy Singletons
	Camera::Destroy();
	TextureManager::Destroy();
	CollisionManager::DestroyInstance();

	delete m_2dRenderer;
}

void Application2D::update(float deltaTime)
{

	// input
	aie::Input* input = aie::Input::getInstance();

	// Reset Camera Resolution
	float resX, resY;
	resX = (float)getWindowWidth();
	resY = (float)getWindowHeight();
	Camera::GetInstance()->SetResolution(Vector2(resX, resY));

	// Update StateMachine
	m_pStateMachine->Update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() 
{

	// wipe the screen to the background colour
	clearScreen();

	// Get CameraPosition
	Vector2 cameraPos = Camera::GetInstance()->GetPosition();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(cameraPos.x, cameraPos.y);

	// begin drawing sprites
	m_2dRenderer->begin();

	// Draw StateMachine
	m_pStateMachine->Draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();

	// IMGUI DEBUG STUFF
	ImGui::Begin("DebugMouseGUI##0");
	// Show FPS
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	ImGui::Separator();

	// Mouse Pos
	ImGui::Text("Mouse Position");

	aie::Input* input = aie::Input::getInstance();
	Vector2 mousePos = Camera::GetInstance()->GetPosition();
	mousePos.x += input->getMouseX();
	mousePos.y += input->getMouseY();

	ImGui::Text("X Pos = %f", mousePos.x);
	ImGui::SameLine();
	ImGui::Text("Y Pos = %f", mousePos.y);


	ImGui::End();
}