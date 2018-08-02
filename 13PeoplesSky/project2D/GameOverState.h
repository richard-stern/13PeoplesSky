#pragma once

#include "BaseState.h"

#include <vector>

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

	// the latest score
	int m_lastScore;
	// list of all scores for high score table
	std::vector<GameOverScore> m_allScores;
};

