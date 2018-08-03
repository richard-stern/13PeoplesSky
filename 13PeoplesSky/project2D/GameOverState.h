#pragma once

#include "BaseState.h"

#include <vector>

#include "Vector2.h"

// changing the name length will break previous saves!
#define NAME_LENGTH 3
#define SAVE_NAME "scores.sav"

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
	aie::Font* m_titleFont;

	aie::Texture* m_banner;
	aie::Texture* m_upArrow;
	aie::Texture* m_downArrow;
	aie::Texture* m_background;

	aie::Texture* m_duckBody;
	aie::Texture* m_duckHead;
	aie::Texture* m_bloodPool;
	Vector2 m_duckHeadPosition;
	float m_duckHeadVelocity;
	float m_bloodPoolSize;
	bool m_bloodPoolSpreading;


	Vector2 m_bannerSize;

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

	void DrawBanner(aie::Renderer2D* pRenderer, float xPos, float yPos);
	void DrawNameSelection(aie::Renderer2D* pRenderer);
	void DrawScoreList(aie::Renderer2D* pRenderer);

	void DrawLetter(aie::Renderer2D* pRenderer, char letter, 
		float posX, float posY, bool selected);

	void DrawCenteredText(aie::Renderer2D* pRenderer, const char* text,
		float posX, float posY, aie::Font* font = nullptr);

	void SaveScores();
	void LoadScores();
};

