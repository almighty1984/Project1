#pragma once

#include "GameState.h"
#include "Object.h"
#include "BitmapFont.h"
#include "Level.h"
#include "Player.h"
#include "TextBox.h"

#include <string>

class cMenuState : public cGameState
{
public:
	cMenuState();
	cMenuState(cLevel *level);
	~cMenuState();
	void clear();
	void init();
	
	void initTextBox();
	void initMenuItems(cApp *app);
	void initObjects(cApp *app);
	virtual void exit(cApp *app);
	virtual void enter(cApp *app, cGameState *previousState);
	virtual void update(cApp *app, float time);


	void updateMenuItems(cApp *app, float time);
	void setMenuItemsColor(unsigned char r, unsigned char g, unsigned char b);
	void setMenuIsHidden(unsigned short menuNumber, bool isHidden);

	virtual void render(cApp *app);		
private:
	//unsigned short m_timerState;
	unsigned char m_menuNumber;
	unsigned char m_slotNumber;
	unsigned char m_numScrollingTexts;
	bool m_doBeginPlayState;
	cTextBox m_textBox;	
	cObject m_logo;
	std::vector<cObject*> m_iconsVitality;
	std::vector<cObject*> m_iconsStamina;
	std::vector<cObject*> m_iconsCoins;
	std::vector<cBitmapFont*> m_fontsSlot;
	std::vector<cBitmapFont*> m_fontsCoins;
	std::vector<cBitmapFont*> m_fontsVitality;
	std::vector<cBitmapFont*> m_fontsStamina;
	std::vector<cBitmapFont*> m_fontsClear;
	cBitmapFont m_fontArrow;
	cBitmapFont m_fontStart;
	cBitmapFont m_fontOptions;
	cBitmapFont m_fontExit;

	//std::vector<cBitmapFont*> m_fontsCredits;

	cBitmapFont m_fontFullscreen, m_fontFullscreenValue;
	cBitmapFont m_fontWidescreen, m_fontWidescreenValue;
	cBitmapFont m_fontVsync, m_fontVsyncValue;
	cBitmapFont m_fontResolution, m_fontResolutionValue;
	cBitmapFont m_fontMusic, m_fontMusicValue;
	cBitmapFont m_fontMusicVolume, m_fontMusicVolumeValue;
	cBitmapFont m_fontJumpLock, m_fontJumpLockValue;
	cBitmapFont m_fontHoverLock, m_fontHoverLockValue;
	cBitmapFont m_fontFps;
	std::stringstream m_strStream;
	std::string m_pathLevel;
	std::string m_pathSave;
	std::string m_playerStart, m_playerState;	
};