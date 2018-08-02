#pragma once

#include "BaseState.h"

#include <vector>

#define NAME_LENGTH 3

// little struct to contain both a name and a score for use in the leaderboards
struct GameOverScore
{
	int score;
	std::string name;
};

class GameOverState :
	public BaseState
{
public:
	GameOverState();
	~GameOverState();

	void Enter() override;
	void Update(float fDeltaTime, StateMachine* pStateMachine) override;
	void Draw(aie::Renderer2D* pRenderer) override;
	void Exit() override;
	
private:
	aie::Font* m_font;
	aie::Font* m_largeFont;

	aie::Texture* m_upArrow;
	aie::Texture* m_downArrow;
	aie::Texture* m_background;

	float m_arrowTimer;
	float m_holdTimer;

	// the latest score
	int m_lastScore;
	// list of all scores for high score table
	std::vector<GameOverScore> m_allScores;

	// name submission stuff
	bool m_hasSubmitted; // have we submitted
	char m_currentName[NAME_LENGTH + 1]; // name being entered
	int m_nameIndex; // current letter being changed

	void UpdateNameSelection(float fDeltaTime);
	void SubmitCurrentName();

	void DrawNameSelection(aie::Renderer2D* pRenderer);
	void DrawScoreList(aie::Renderer2D* pRenderer);

	void DrawLetter(aie::Renderer2D* pRenderer, char letter, 
		float posX, float posY, bool selected);

	void DrawCenteredText(aie::Renderer2D* pRenderer, const char* text,
		float posX, float posY, aie::Font* font = nullptr);
};

