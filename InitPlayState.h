#pragma once
#include "GameState.h"

class cInitPlayState : public cGameState
{
public:
	cInitPlayState();
	cInitPlayState(std::string pathLevel, sStartInfo startInfo);
	~cInitPlayState();

	virtual void enter(cApp* app, cGameState* previousState);
	virtual void exit(cApp* app);
	virtual void init(std::string pathLevel, sStartInfo startInfo);
	virtual void update(cApp* app, float time);
private:
	std::string m_pathLevel;
	std::string m_playerStart, m_playerState;
	bool m_isFacingLeft, m_doStartUnlocked;
	float m_velocityX;
};