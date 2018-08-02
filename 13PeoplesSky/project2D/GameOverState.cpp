#include "GameOverState.h"

#include <cassert>
#include <Input.h>
#include <algorithm>

#include "GUI.h"
#include "Camera.h"
#include "StateMachine.h"
#include "TextureManager.h"

GameOverState::GameOverState()
{
	TextureManager* manager = TextureManager::GetInstance();
	assert(manager && "Texture manager should exist!");

	m_font = manager->LoadFont("./font/consolas.ttf", 36);
	m_largeFont = manager->LoadFont("./font/consolas.ttf", 48);

	m_upArrow = manager->LoadTexture("./textures/up_arrow.png");
	m_downArrow = manager->LoadTexture("./textures/down_arrow.png");
	m_background = manager->LoadTexture("./textures/menuBackground.png");
}

GameOverState::~GameOverState() { }

void GameOverState::Enter()
{
	// grab the score from the GUI
	//m_lastScore = GUI::GetInstance()->GetScore();
	m_lastScore = rand() % 420;

	// score hasn't been submitted to the high scores table
	m_hasSubmitted = false;
	// fill the name field with As
	memset(m_currentName, 'A', sizeof(char) * 4);
	// EXCEPT the last one, which should be null terminator
	m_currentName[NAME_LENGTH] = 0;
	m_nameIndex = 0;

	m_arrowTimer = 0.0f;

	Vector2 windowSize = Camera::GetInstance()->GetResolution();
	Camera::GetInstance()->SetPosition(windowSize.x/2, windowSize.y/2);
}

void GameOverState::Update(float fDeltaTime, StateMachine* pStateMachine)
{
	if (!m_hasSubmitted)
	{
		UpdateNameSelection(fDeltaTime);
		return;
	}

	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		pStateMachine->ChangeState(ESTATE_MENU);
}

void GameOverState::Draw(aie::Renderer2D* pRenderer)
{
	Vector2 windowSize = Camera::GetInstance()->GetResolution();
	pRenderer->drawSprite(m_background, 0.0f, 0.0f, windowSize.x, windowSize.y,
		0.0f, 100.0f, 0.0f, 0.0f);
	if (!m_hasSubmitted)
		DrawNameSelection(pRenderer);
	else
		DrawScoreList(pRenderer);
}

void GameOverState::Exit() { }

void GameOverState::UpdateNameSelection(float fDeltaTime)
{
	m_arrowTimer += fDeltaTime;

	aie::Input* input = aie::Input::getInstance();

	// moving between letters
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
		m_nameIndex--;
	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
		m_nameIndex++;

	// make selection wrap around
	if (m_nameIndex < 0)
		m_nameIndex = NAME_LENGTH - 1;
	if (m_nameIndex >= NAME_LENGTH)
		m_nameIndex = 0;

	if (m_holdTimer > 0.0f)
		m_holdTimer -= fDeltaTime;

	if (input->wasKeyPressed(aie::INPUT_KEY_UP) ||
		input->wasKeyPressed(aie::INPUT_KEY_DOWN))
		m_holdTimer = 0.0f;

	// handle changing letters
	const float holdDelay = 0.05f;
	if (input->isKeyDown(aie::INPUT_KEY_UP) && m_holdTimer <= 0.0f)
	{
		m_currentName[m_nameIndex]--;
		m_holdTimer = holdDelay;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN) && m_holdTimer <= 0.0f)
	{
		m_currentName[m_nameIndex]++;
		m_holdTimer = holdDelay;
	}

	// start timer for holding down key
	if (input->wasKeyPressed(aie::INPUT_KEY_UP) ||
		input->wasKeyPressed(aie::INPUT_KEY_DOWN))
		m_holdTimer = 0.5f;

	// make letters wrap around from A to Z
	if (m_currentName[m_nameIndex] < 'A')
		m_currentName[m_nameIndex] = 'Z';
	if (m_currentName[m_nameIndex] > 'Z')
		m_currentName[m_nameIndex] = 'A';

	// handle submission
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
		SubmitCurrentName();
}

void GameOverState::SubmitCurrentName()
{
	// make struct containing name and score
	GameOverScore newScore;
	newScore.name = std::string(m_currentName);
	newScore.score = m_lastScore;

	m_allScores.push_back(newScore);

	// now we can sort scores by score
	std::sort(m_allScores.begin(), m_allScores.end(), [](auto a, auto b)
	{
		return a.score > b.score;
	});

	m_hasSubmitted = true;
}

void GameOverState::DrawNameSelection(aie::Renderer2D* pRenderer)
{
	// grab the size of the window 
	Vector2 windowSize = Camera::GetInstance()->GetResolution();

	// make score text
	char scoreText[32];
	sprintf_s(scoreText, 32, "Your Score: %i", m_lastScore);

	// grab the width of the string so we can center it
	float scoreWidth = m_font->getStringWidth(scoreText);
	// and store the center position here for cleanliness
	float centerPos = windowSize.x / 2.0f - scoreWidth / 2.0f;

	// print it somewhere in the middle of the screen
	pRenderer->setRenderColour(0xffffffff);
	pRenderer->drawText(m_font, scoreText, centerPos, 200.0f);

	// get some numbers to draw the name in the middle of the screen
	const float letterWidth = 32.0f;
	const float wordWidth = letterWidth * NAME_LENGTH;

	const float namePos = windowSize.x / 2.0f;
	const float startPos = namePos - (wordWidth*0.5f);
	// draw the letters individually
	for (int i = 0; i < NAME_LENGTH; ++i)
	{
		char letter = m_currentName[i];
		float posX = startPos + i * letterWidth;

		DrawLetter(pRenderer, letter, posX, 400, m_nameIndex == i);
	}

	DrawCenteredText(pRenderer, "Use ARROW KEYS to input your name", 
		windowSize.x/2.0f, 60.0f);
	DrawCenteredText(pRenderer, "Press ENTER to submit score", 
		windowSize.x/2.0f, 30.0f);
}

void GameOverState::DrawScoreList(aie::Renderer2D* pRenderer)
{
	Vector2 windowSize = Camera::GetInstance()->GetResolution();

	const float lineWidth = 3.0f;

	const float centerX = windowSize.x / 2.0f;
	const float tableWidth = 400.0f;
	const float cellWidth = tableWidth / 2.0f;

	// x positions of the horizontal lines
	const float lineX1 = centerX - cellWidth;
	const float lineX2 = centerX + cellWidth;

	const int tableRows = 10;
	const float cellHeight = 40.0f;

	float tableY = windowSize.y - 200.0f;
	const float tableBottom = tableY - (cellHeight * (tableRows));

	pRenderer->setRenderColour(0xff00ff80);
	pRenderer->drawBox(centerX, (tableY + tableBottom) / 2.0f, tableWidth,
		tableY - tableBottom);

	pRenderer->setRenderColour(0xffffffff);
	// draw vertical lines at the sides
	pRenderer->drawLine(lineX1, tableY, lineX1, tableBottom, lineWidth);
	pRenderer->drawLine(lineX2, tableY, lineX2, tableBottom, lineWidth);
	// and down the middle
	pRenderer->drawLine(centerX, tableY, centerX, tableBottom, lineWidth);

	for (int i = 0; i < tableRows; ++i)
	{

		pRenderer->drawLine(lineX1, tableY, lineX2, tableY, lineWidth);

		tableY -= cellHeight;
		if (i >= (int)m_allScores.size())
			continue;
		// draw score info
		float scoreY = tableY - 3.0f;
		std::string scoreText = std::to_string(m_allScores[i].score);

		float cell1Center = centerX - cellWidth / 2.0f;
		float cell2Center = centerX + cellWidth / 2.0f;

		DrawCenteredText(pRenderer, m_allScores[i].name.c_str(),
			cell1Center, scoreY);
		DrawCenteredText(pRenderer, scoreText.c_str(),
			cell2Center, scoreY);
	}
	pRenderer->drawLine(lineX1, tableY, lineX2, tableY, lineWidth);

	DrawCenteredText(pRenderer, "Press SPACE to return to menu", centerX,
		30.0f);
}

void GameOverState::DrawLetter(aie::Renderer2D* pRenderer, char letter,
	float posX, float posY, bool selected)
{
	// make a null-terminated string from the character
	char str[2];
	str[0] = letter;
	str[1] = 0;

	// grab the size of the letter so we can center it
	// also used for placing the selection arrows
	float letterWidth, letterHeight;
	m_largeFont->getStringSize(str, letterWidth, letterHeight);
	letterWidth = m_largeFont->getStringWidth(str);
	float centerPos = posX - letterWidth / 2.0f;

	// draw the letter
	pRenderer->drawText(m_largeFont, str, centerPos, posY);

	if (!selected)
		return;

	const float waveAmt = 10.0f;
	float waveOffset = fabsf(sinf(m_arrowTimer * 4.0f)) * waveAmt;

	float upArrowY = posY + letterHeight + 10.0f + waveOffset;
	float downArrowY = posY - 10.0f - waveOffset;

	pRenderer->drawSprite(m_upArrow, posX, upArrowY);
	pRenderer->drawSprite(m_downArrow, posX, downArrowY);
}

void GameOverState::DrawCenteredText(aie::Renderer2D* pRenderer,
	const char* text, float posX, float posY)
{
	float sWidth, sHeight;
	m_font->getStringSize(text, sWidth, sHeight);

	pRenderer->drawText(m_font, text, posX - sWidth / 2.0f,
		posY + sHeight / 2.0f);
}
