#include "GameOverState.h"

#include <cassert>
#include <Input.h>
#include <fstream>
#include <algorithm>

#include "GUI.h"
#include "Camera.h"
#include "StateMachine.h"
#include "TextureManager.h"

GameOverState::GameOverState()
{
	TextureManager* manager = TextureManager::GetInstance();
	assert(manager && "Texture manager should exist!");

	m_font = manager->LoadFont("./font/consolas.ttf", 24);
	m_largeFont = manager->LoadFont("./font/consolas.ttf", 48);
	m_titleFont = manager->LoadFont("./font/consolas.ttf", 64);

	m_upArrow = manager->LoadTexture("./textures/up_arrow.png");
	m_downArrow = manager->LoadTexture("./textures/down_arrow.png");
	m_banner = manager->LoadTexture("./textures/gameOverBanner.png");
	m_background = manager->LoadTexture("./textures/gameOverBackground.png");

	m_duckBody = manager->LoadTexture("./textures/deadDuckBody.png");
	m_duckHead = manager->LoadTexture("./textures/deadDuckHead.png");
	m_bloodPool = manager->LoadTexture("./textures/bloodPool.png");

	// grab the banner size so we can properly scale it
	m_bannerSize.x = (float)m_banner->getWidth();
	m_bannerSize.y = (float)m_banner->getHeight();
}

GameOverState::~GameOverState() { }

void GameOverState::Enter()
{
	// grab the score from the GUI
	m_lastScore = GUI::GetInstance()->GetScore();

	// score hasn't been submitted to the high scores table
	m_hasSubmitted = false;
	// fill the name field with As
	memset(m_currentName, 'A', sizeof(char) * 4);
	// EXCEPT the last one, which should be null terminator
	m_currentName[NAME_LENGTH] = 0;
	m_nameIndex = 0;

	m_arrowTimer = 0.0f;

	Vector2 windowSize = Camera::GetInstance()->GetResolution();
	Camera::GetInstance()->SetPosition(windowSize.x / 2, windowSize.y / 2);

	m_duckHeadPosition.x = windowSize.x - 220.0f;
	m_duckHeadPosition.y = windowSize.y + 500.0f;
	m_duckHeadVelocity = -1000.0f;
	m_bloodPoolSize = 0.0f;
	m_bloodPoolSpreading = false;

	LoadScores();
}

void GameOverState::Update(float fDeltaTime, StateMachine* pStateMachine)
{
	m_duckHeadVelocity -= 5000.0f * fDeltaTime;
	m_duckHeadPosition.y += m_duckHeadVelocity * fDeltaTime;

	if (m_duckHeadPosition.y < 128.0f)
	{
		m_duckHeadPosition.y = 128.0f;
		m_duckHeadVelocity = -m_duckHeadVelocity / 3.0f;
		if (m_duckHeadVelocity < 350)
			m_bloodPoolSpreading = true;
	}

	if (m_bloodPoolSpreading)
		m_bloodPoolSize -= (m_bloodPoolSize - 256.0f) * fDeltaTime;

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

	pRenderer->drawSprite(m_background, windowSize.x / 2.0f, windowSize.y / 2.0f,
		windowSize.x, windowSize.y);

	DrawBanner(pRenderer, windowSize.x / 2.0f, windowSize.y - 140.0f);

	// draw blood pool :D
	if (m_bloodPoolSpreading)
		pRenderer->drawSprite(m_bloodPool, m_duckHeadPosition.x, 88.0f,
			m_bloodPoolSize, m_bloodPoolSize);

	const float duckSize = 256.0f;

	// draw duck body
	pRenderer->drawSprite(m_duckBody, 220.0f, 128.0f, duckSize, duckSize);
	pRenderer->drawSprite(m_duckHead, m_duckHeadPosition.x, m_duckHeadPosition.y,
		duckSize, duckSize);


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

	bool downPressed = input->wasKeyPressed(aie::INPUT_KEY_S) ||
		input->wasKeyPressed(aie::INPUT_KEY_DOWN);
	bool upPressed = input->wasKeyPressed(aie::INPUT_KEY_W) ||
		input->wasKeyPressed(aie::INPUT_KEY_UP);
	bool leftPressed = input->wasKeyPressed(aie::INPUT_KEY_A) ||
		input->wasKeyPressed(aie::INPUT_KEY_LEFT);
	bool rightPressed = input->wasKeyPressed(aie::INPUT_KEY_D) ||
		input->wasKeyPressed(aie::INPUT_KEY_RIGHT);

	bool downHeld = input->isKeyDown(aie::INPUT_KEY_S) ||
		input->isKeyDown(aie::INPUT_KEY_DOWN);
	bool upHeld = input->isKeyDown(aie::INPUT_KEY_W) ||
		input->isKeyDown(aie::INPUT_KEY_UP);

	// moving between letters
	if (leftPressed)
		m_nameIndex--;
	if (rightPressed)
		m_nameIndex++;

	// make selection wrap around
	if (m_nameIndex < 0)
		m_nameIndex = NAME_LENGTH - 1;
	if (m_nameIndex >= NAME_LENGTH)
		m_nameIndex = 0;

	if (m_holdTimer > 0.0f)
		m_holdTimer -= fDeltaTime;

	if (upPressed || downPressed)
		m_holdTimer = 0.0f;

	// handle changing letters
	const float holdDelay = 0.1f;
	if (upHeld && m_holdTimer <= 0.0f)
	{
		m_currentName[m_nameIndex]--;
		m_holdTimer = holdDelay;
	}
	if (downHeld && m_holdTimer <= 0.0f)
	{
		m_currentName[m_nameIndex]++;
		m_holdTimer = holdDelay;
	}

	// start timer for holding down key
	if (upPressed || downPressed)
		m_holdTimer = 0.3f;

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
	SaveScores();
}

void GameOverState::DrawBanner(aie::Renderer2D * pRenderer, float xPos, float yPos)
{
	Vector2 windowSize = Camera::GetInstance()->GetResolution();

	// draw banner stuff
	const float bannerSizeFactor = 0.7f;
	float bannerWidth = m_bannerSize.x * bannerSizeFactor;
	if (bannerWidth < windowSize.x)
		bannerWidth = windowSize.x;

	pRenderer->drawSprite(m_banner, windowSize.x / 2.0f, yPos,
		bannerWidth, m_bannerSize.y * bannerSizeFactor);

	// banner text
	DrawCenteredText(pRenderer, "GAME OVER", windowSize.x / 2.0f,
		yPos, m_titleFont);
}

void GameOverState::DrawNameSelection(aie::Renderer2D* pRenderer)
{
	// grab the size of the window 
	Vector2 windowSize = Camera::GetInstance()->GetResolution();

	// make score text
	char scoreText[32];
	sprintf_s(scoreText, 32, "Your Score: %i", m_lastScore);

	// print it somewhere in the middle of the screen
	pRenderer->setRenderColour(0xffffffff);

	// get some numbers to draw the name in the middle of the screen
	const float letterWidth = 32.0f;
	const float wordWidth = letterWidth * NAME_LENGTH;

	const float namePos = windowSize.x / 2.0f;
	const float startPos = namePos - (wordWidth*0.5f);
	const float letterPosY = windowSize.y - 380.0f;
	// draw the letters individually
	for (int i = 0; i < NAME_LENGTH; ++i)
	{
		char letter = m_currentName[i];
		float posX = startPos + i * letterWidth;

		DrawLetter(pRenderer, letter, posX, letterPosY, m_nameIndex == i);
	}


	DrawCenteredText(pRenderer, "Enter your name:", windowSize.x / 2.0f,
		letterPosY + 120);

	DrawCenteredText(pRenderer, scoreText, windowSize.x / 2.0f,
		letterPosY - 80);

	DrawCenteredText(pRenderer, "Use WASD to input your name",
		windowSize.x / 2.0f, 60.0f);
	DrawCenteredText(pRenderer, "Press ENTER to submit score",
		windowSize.x / 2.0f, 30.0f);
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

	const int tableRows = 7;
	const float cellHeight = 40.0f;

	float tableY = windowSize.y - 330.0f;
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

	float cell1Center = centerX - cellWidth / 2.0f;
	float cell2Center = centerX + cellWidth / 2.0f;

	DrawCenteredText(pRenderer, "Name", cell1Center, tableY + cellHeight / 2.0f);
	DrawCenteredText(pRenderer, "Score", cell2Center, tableY + cellHeight / 2.0f);
	DrawCenteredText(pRenderer, "HIGH SCORES", windowSize.x / 2.0f,
		tableY + 70, m_largeFont);

	for (int i = 0; i < tableRows; ++i)
	{
		pRenderer->drawLine(lineX1, tableY, lineX2, tableY, lineWidth);

		tableY -= cellHeight;
		if (i >= (int)m_allScores.size())
			continue;
		// draw score info
		float scoreY = tableY + cellHeight / 2.0f;
		std::string scoreText = std::to_string(m_allScores[i].score);


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
	const char* text, float posX, float posY, aie::Font* font)
{
	if (!font)
		font = m_font;

	float sWidth, sHeight;
	font->getStringSize(text, sWidth, sHeight);

	pRenderer->drawText(font, text, posX - sWidth / 2.0f,
		posY - sHeight / 2.0f);
}

void GameOverState::SaveScores()
{
	std::fstream file;
	file.open(SAVE_NAME, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		printf("Couldn't open high scores file to save!\n");
		return;
	}

	int scoreCount = (int)m_allScores.size();

	file.write((char*)&scoreCount, 4);

	for (int i = 0; i < scoreCount; ++i)
	{
		GameOverScore score = m_allScores[i];

		int points = score.score;
		char name[NAME_LENGTH + 1];
		name[NAME_LENGTH] = 0;
		strcpy(name, score.name.c_str());

		file.write(name, sizeof(char) * NAME_LENGTH);
		file.write((char*)&points, 4);
	}

	file.close();
}

void GameOverState::LoadScores()
{
	std::fstream file;
	file.open(SAVE_NAME, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		printf("Couldn't open high scores file to load!\n");
		return;
	}

	int scoreCount;
	file.read((char*)&scoreCount, 4);

	m_allScores.clear();
	for (int i = 0; i < scoreCount; ++i)
	{
		int points;
		char name[NAME_LENGTH + 1];
		name[NAME_LENGTH] = 0;
		file.read(name, NAME_LENGTH);
		file.read((char*)&points, 4);

		m_allScores.push_back({ points, std::string(name) });
	}

	file.close();
}
