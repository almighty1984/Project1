#pragma once
#include "GameState.h"
#include "Player.h"
#include "CameraManager.h"
#include "Object.h"
#include "TextBox.h"

// This class does something.
class cPlayState : public cGameState
{
public:
	cPlayState();
	cPlayState(cLevel* level, std::string levelPath, sStartInfo startInfo);
	~cPlayState();

	virtual void enter(cApp* app, cGameState* previousState);
	virtual void exit(cApp* app);
	virtual void init(const std::string& pathLevel, sStartInfo startInfo);
	virtual void update(cApp* app, float time);
	virtual void render(cApp* app);

	void initPlayerStart(cApp *app);

	// Checks if we should change level and to what, set new level path and player start to arguments passed.
	bool checkChangeLevel(cApp *app, cPlayer& player, std::string& newPathLevel, std::string& newPlayerStart);

private:


	//cLevel m_level;
	cPlayer m_player1;
	//cPlayer m_player2;

	std::string m_nextForeground;
	std::string m_playerStart, m_playerState;

	std::string m_pathLevel;

	bool m_doChangeLevel;
	bool m_doQuitToMenu;
	bool m_doStartUnlocked;

	//float m_timerPositionX, m_timerPositionY;
	//cBitmapFont m_fontHours, m_fontMinutes, m_fontSeconds, m_fontMs;
	
	cBitmapFont m_fontFps;
	cBitmapFont m_fontCoins;	

	cObject m_iconCoins;
	cObject m_meterVitalityBackground, m_meterStaminaBackground, m_meterVitality, m_meterStamina;	

	cBitmapFont m_fontVitality, m_fontStamina;
	cTextBox m_textBox;	

	//unsigned short i,j,k;
	short m_tileX, m_tileY;
	short m_entityTileX, m_entityTileY;
	//short m_oldEntityTileX, m_oldEntityTileY;

	//std::stringstream m_strStream;
	unsigned short m_prevNumCoins;
	
	//unsigned int m_playTimerHours, m_playTimerMinutes, m_playTimerSeconds, m_playTimerMs;

	/*int m_mapOffsetX, m_mapOffsetY;
	int m_mapMovementX, m_mapMovementY;*/
	
	/*float m_previousMapPositionX;
	float m_previousMapPositionY;*/

	bool m_inExitMenu;
	
	bool m_activatedTextSign;

	float m_velocityX;

};