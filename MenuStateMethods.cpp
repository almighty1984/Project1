#include "MenuState.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include "MusicManager.h"

void cMenuState::clear() {
	m_strStream.clear();
	m_pathLevel.clear();
	m_pathSave.clear();
	m_playerStart.clear();
	/*for (unsigned char i = 0; i < 3; ++i) {
		m_fontsSlot.at(i)->clearText();
		m_fontsCoins.at(i)->clearText();
		m_fontsVitality.at(i)->clearText();
		m_fontsStamina.at(i)->clearText();
		m_fontsClear.at(i)->clearText();
	}*/
	m_fontsSlot.clear();
	m_fontsCoins.clear();
	m_fontsVitality.clear();
	m_fontsStamina.clear();
	m_fontsClear.clear();
	m_iconsVitality.clear();
	m_iconsStamina.clear();
	m_iconsCoins.clear();
	cRenderingManager::clearBackgroundPlanes();
	cRenderingManager::clearForegroundPlanes();
	cRenderingManager::clearPlayers();
	cRenderingManager::clearBitmapFonts();
	cRenderingManager::clearParticles();
	cRenderingManager::clearLevel();

	if (m_levelPtr != nullptr) {
		delete m_levelPtr;
		m_levelPtr = nullptr;
	}
}

void cMenuState::init() {
	std::cout << "cMenuState::init() start" << "\n";
	m_doBeginPlayState = false;
	m_menuNumber = 0;
	m_slotNumber = 0;
	m_numScrollingTexts = 3;
	//cMusicManager::stopMusicBackground();
	m_secondCall = false;
	m_hasMouseMoved = false;
	m_doDarkenWeather = false;
	m_doLightenWeather = false;
	m_weatherColor = 255.0f;
	m_mouseX = 0;
	m_mouseY = 0;
	m_joyMovedX = 0.0f;
	m_joyMovedY = 0.0f;
	for (int i = 0; i < 323; ++i) {
		keysHeld[i] = false;
		joyButtonsHeld[i] = false;
	}

	strncpy_s(m_alphabet, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", sizeof(m_alphabet) - 1);
	m_strStream.clear();
	cSavesManager::clearPlayerStatus();
	m_playerStart = "center";
	m_playerState = "grass";
	//m_pathLevel = "Data\\Levels\\menu_start.bin";
}

void cMenuState::initTextBox() {
	//m_textBox.clear();	
	m_textBox.loadConfig("Data\\TextBoxes\\menu.cfg");
	m_textBox.setupBoxObjects(10, 2);
	m_textBox.setX(80);
	m_textBox.setY(192);
	m_textBox.setIsHidden(true);
	m_textBox.setDoHide(true);
}

void cMenuState::initObjects(cApp *app) {
	

	//m_logo.setImagePath("Data\\Objects\\Images\\logo.png");
	m_logo.setX(120);
	m_logo.setY(32);

	m_logo.loadConfig("Data\\Objects\\logo.cfg");
	//m_logo.setIsHidden(true);

	/*for (unsigned char i = 0; i < m_numScrollingTexts; ++i) {
		m_fontsCredits.push_back(new cBitmapFont);
		m_fontsCredits.at(i)->setWidth(320);
		m_fontsCredits.at(i)->setImagePath("Data\\Fonts\\font_8_brown.png");
		if (i == 0) {
			m_fontsCredits.at(i)->setText("Art by Paer Martinsson");
			m_fontsCredits.at(i)->setX((float)(320 + 48));
		}
		else if (i == 1) {
			m_fontsCredits.at(i)->setText("Code, art, audio by Daniel Alm");
			m_fontsCredits.at(i)->setX(m_fontsCredits.at(i - 1)->getX() + (float)((160 + 48) + m_fontsCredits.at(i - 1)->getTextSize() * 8));
		}
		else if (i == 2) {
			m_fontsCredits.at(i)->setText("Epstein didn't kill himself");
			m_fontsCredits.at(i)->setX(m_fontsCredits.at(i - 1)->getX() + (float)((160 + 48) + m_fontsCredits.at(i - 1)->getTextSize() * 8));
		}
		std::cout << "TextSize " << (int)i << " " << m_fontsCredits.at(i)->getTextSize() << "\n";

		m_fontsCredits.at(i)->setY(224.0f);
		m_fontsCredits.at(i)->setVelocityX(-1.5f);
	}*/

	m_fontArrow.setText("->");
	m_fontArrow.setImagePath(cRenderingManager::getPathFont());
	m_fontArrow.setX(136 - 16);
	m_fontArrow.setY(240 / 2);
	m_fontArrow.setWidth(16);
	m_fontArrow.setIsHidden(false);

	m_fontStart.setWidth(128);
	m_fontStart.setText("Start");
	m_fontStart.setImagePath(cRenderingManager::getPathFont());
	m_fontStart.setX(136);
	m_fontStart.setY(240 / 2);
	m_fontStart.setIsHidden(false);

	m_fontOptions.setWidth(128);
	m_fontOptions.setText("Options");
	m_fontOptions.setImagePath(cRenderingManager::getPathFont());
	m_fontOptions.setX(136);
	m_fontOptions.setY(240 / 2 + 16);
	m_fontOptions.setIsHidden(false);

	m_fontExit.setWidth(128);
	m_fontExit.setText("Exit");
	m_fontExit.setImagePath(cRenderingManager::getPathFont());
	m_fontExit.setX(136);
	m_fontExit.setY(240 / 2 + 32);
	m_fontExit.setIsHidden(false);

	m_fontFullscreen.setWidth(128);
	m_fontFullscreen.setText("Fullscreen");
	m_fontFullscreen.setImagePath(cRenderingManager::getPathFont());
	m_fontFullscreen.setX(96);
	m_fontFullscreen.setY(80 + 16);
	m_fontFullscreen.setIsHidden(true);

	m_fontFullscreenValue.setWidth(128);
	m_fontFullscreenValue.setText(app->getIsFullscreen() ? "true" : "false");
	m_fontFullscreenValue.setImagePath(cRenderingManager::getPathFont());
	m_fontFullscreenValue.setX(136 + 64);
	m_fontFullscreenValue.setY(80 + 16);
	m_fontFullscreenValue.setIsHidden(true);

	m_fontWidescreen.setWidth(128);
	m_fontWidescreen.setText("Widescreen");
	m_fontWidescreen.setImagePath(cRenderingManager::getPathFont());
	m_fontWidescreen.setX(96);
	m_fontWidescreen.setY(80 + 24);
	m_fontWidescreen.setIsHidden(true);

	m_fontWidescreenValue.setWidth(128);
	m_fontWidescreenValue.setText(app->getIsWidescreen() ? "true" : "false");
	m_fontWidescreenValue.setImagePath(cRenderingManager::getPathFont());
	m_fontWidescreenValue.setX(136 + 64);
	m_fontWidescreenValue.setY(80 + 24);
	m_fontWidescreenValue.setIsHidden(true);

	m_fontVsync.setWidth(128);
	m_fontVsync.setText("Vsync");
	m_fontVsync.setImagePath(cRenderingManager::getPathFont());
	m_fontVsync.setX(96);
	m_fontVsync.setY(80 + 32);
	m_fontVsync.setIsHidden(true);

	m_fontVsyncValue.setWidth(128);
	m_fontVsyncValue.setText(app->getUseVerticalSync() ? "true" : "false");
	m_fontVsyncValue.setImagePath(cRenderingManager::getPathFont());
	m_fontVsyncValue.setX(136 + 64);
	m_fontVsyncValue.setY(80 + 32);
	m_fontVsyncValue.setIsHidden(true);

	m_fontResolution.setWidth(128);
	m_fontResolution.setText("Resolution");
	m_fontResolution.setImagePath(cRenderingManager::getPathFont());
	m_fontResolution.setX(96);
	m_fontResolution.setY(80 + 40);
	m_fontResolution.setIsHidden(true);

	m_fontResolutionValue.setWidth(128);
	if (app->getWindowMultiplier() == 1.0f) {
		m_fontResolutionValue.setText("1x");
	}
	else if (app->getWindowMultiplier() == 2.0f) {
		m_fontResolutionValue.setText("2x");
	}
	else if (app->getWindowMultiplier() == 3.0f) {
		m_fontResolutionValue.setText("3x");
	}
	m_fontResolutionValue.setImagePath(cRenderingManager::getPathFont());
	m_fontResolutionValue.setX(136 + 64);
	m_fontResolutionValue.setY(80 + 40);
	m_fontResolutionValue.setIsHidden(true);

	m_fontMusic.setWidth(128);
	m_fontMusic.setText("Music");
	m_fontMusic.setImagePath(cRenderingManager::getPathFont());
	m_fontMusic.setX(96);
	m_fontMusic.setY(80 + 48);
	m_fontMusic.setIsHidden(true);

	m_fontMusicValue.setWidth(128);
	m_fontMusicValue.setText(cMusicManager::getDoPlay() ? "true" : "false");
	m_fontMusicValue.setImagePath(cRenderingManager::getPathFont());
	m_fontMusicValue.setX(136 + 64);
	m_fontMusicValue.setY(80 + 48);
	m_fontMusicValue.setIsHidden(true);

	m_fontMusicVolume.setWidth(128);
	m_fontMusicVolume.setText("Volume");
	m_fontMusicVolume.setImagePath(cRenderingManager::getPathFont());
	m_fontMusicVolume.setX(96);
	m_fontMusicVolume.setY(80 + 56);
	m_fontMusicVolume.setIsHidden(true);

	m_fontMusicVolumeValue.setWidth(128);
	m_fontMusicVolumeValue.setText(std::to_string((int)(app->getMusicVolume())));
	m_fontMusicVolumeValue.setImagePath(cRenderingManager::getPathFont());
	m_fontMusicVolumeValue.setX(136 + 64);
	m_fontMusicVolumeValue.setY(80 + 56);
	m_fontMusicVolumeValue.setIsHidden(true);

	m_fontJumpLock.setWidth(128);
	m_fontJumpLock.setText("Jump lock");
	m_fontJumpLock.setImagePath(cRenderingManager::getPathFont());
	m_fontJumpLock.setX(96);
	m_fontJumpLock.setY(80 + 64);
	m_fontJumpLock.setIsHidden(true);

	m_fontJumpLockValue.setWidth(128);
	m_fontJumpLockValue.setText(app->getUseJumpLock() ? "true" : "false");
	m_fontJumpLockValue.setImagePath(cRenderingManager::getPathFont());
	m_fontJumpLockValue.setX(136 + 64);
	m_fontJumpLockValue.setY(80 + 64);
	m_fontJumpLockValue.setIsHidden(true);

	m_fontHoverLock.setWidth(128);
	m_fontHoverLock.setText("Hover lock");
	m_fontHoverLock.setImagePath(cRenderingManager::getPathFont());
	m_fontHoverLock.setX(96);
	m_fontHoverLock.setY(80 + 72);
	m_fontHoverLock.setIsHidden(true);

	m_fontHoverLockValue.setWidth(128);
	m_fontHoverLockValue.setText(app->getUseHoverLock() ? "true" : "false");
	m_fontHoverLockValue.setImagePath(cRenderingManager::getPathFont());
	m_fontHoverLockValue.setX(136 + 64);
	m_fontHoverLockValue.setY(80 + 72);
	m_fontHoverLockValue.setIsHidden(true);

	initMenuItems(app);

	m_fontFps.setX(304.0f);
	m_fontFps.setY(0.0f);
	m_fontFps.setWidth(64);

	cRenderingManager::addLevel(m_levelPtr);
	cRenderingManager::addObject(&m_logo);

	/*for (unsigned short i = 0; i < m_fontsCredits.size(); ++i) {
		cRenderingManager::addBitmapFont(m_fontsCredits.at(i));
	}*/

	cRenderingManager::addBitmapFont(&m_fontArrow);
	cRenderingManager::addBitmapFont(&m_fontStart);
	cRenderingManager::addBitmapFont(&m_fontOptions);
	cRenderingManager::addBitmapFont(&m_fontExit);
	cRenderingManager::addBitmapFont(&m_fontFullscreen);	cRenderingManager::addBitmapFont(&m_fontFullscreenValue);
	cRenderingManager::addBitmapFont(&m_fontWidescreen);	cRenderingManager::addBitmapFont(&m_fontWidescreenValue);
	cRenderingManager::addBitmapFont(&m_fontVsync);		cRenderingManager::addBitmapFont(&m_fontVsyncValue);
	cRenderingManager::addBitmapFont(&m_fontResolution);	cRenderingManager::addBitmapFont(&m_fontResolutionValue);
	cRenderingManager::addBitmapFont(&m_fontMusic);		cRenderingManager::addBitmapFont(&m_fontMusicValue);
	cRenderingManager::addBitmapFont(&m_fontMusicVolume);	cRenderingManager::addBitmapFont(&m_fontMusicVolumeValue);
	cRenderingManager::addBitmapFont(&m_fontJumpLock);	cRenderingManager::addBitmapFont(&m_fontJumpLockValue);
	cRenderingManager::addBitmapFont(&m_fontHoverLock);	cRenderingManager::addBitmapFont(&m_fontHoverLockValue);

	for (unsigned char i = 0; i < 3; ++i) {
		cRenderingManager::addBitmapFont(m_fontsSlot.at(i));
		cRenderingManager::addBitmapFont(m_fontsCoins.at(i));
		cRenderingManager::addBitmapFont(m_fontsVitality.at(i));
		cRenderingManager::addObject(m_iconsCoins.at(i));
		cRenderingManager::addObject(m_iconsVitality.at(i));
		cRenderingManager::addObject(m_iconsStamina.at(i));
		cRenderingManager::addBitmapFont(m_fontsStamina.at(i));
		cRenderingManager::addBitmapFont(m_fontsClear.at(i));
	}
	cRenderingManager::addBitmapFont(&m_fontFps);
}

void cMenuState::initMenuItems(cApp* app) {
	std::cout << "cMenuState::initMenuItems()" << "\n";
	//app->loadMapsConfig("Data\\maps.cfg");
	std::string tmpString;
	for (unsigned char i = 0; i < 3; ++i) {
		tmpString.clear();
		tmpString = "Data\\Saves\\" + std::to_string(i) + ".bin";
		std::cout << "tmpString = " << tmpString << "\n";

		cSavesManager::clearCoins();
		//cSavesManager::clearTargetObjects();
		cSavesManager::initSave();
		cSavesManager::setSlotNumber(i);
		cSavesManager::readSave(tmpString);
		m_fontsSlot.push_back(new cBitmapFont);
		m_fontsSlot.at(i)->setWidth(128);
		m_strStream.clear();
		m_strStream.str("");
		m_strStream << (int)i;

		if (cSavesManager::getPlayerName().empty()) {
			m_fontsSlot.at(i)->setText("Slot " + m_strStream.str());
		} else {
			m_fontsSlot.at(i)->setText(cSavesManager::getPlayerName());
		}

		m_fontsSlot.at(i)->setImagePath(cRenderingManager::getPathFont());
		m_fontsSlot.at(i)->setX((float)(72 + 80 * i));
		m_fontsSlot.at(i)->setY((float)(240 / 2 - 32 + 32));
		m_fontsSlot.at(i)->setIsHidden(true);

		m_fontsCoins.push_back(new cBitmapFont);
		m_fontsCoins.at(i)->setWidth(128);
		m_strStream.clear();
		m_strStream.str("");
		m_strStream << cSavesManager::getNumCoins();
		m_fontsCoins.at(i)->setText(m_strStream.str());
		m_fontsCoins.at(i)->setImagePath(cRenderingManager::getPathFont());
		m_fontsCoins.at(i)->setX((float)(72 + 80 * i));
		m_fontsCoins.at(i)->setY((float)(240 / 2 + 32));
		m_fontsCoins.at(i)->setIsHidden(true);

		m_fontsVitality.push_back(new cBitmapFont);
		m_fontsVitality.at(i)->setWidth(64);
		tmpString.clear();
		tmpString = std::to_string(cSavesManager::getPlayerVitality());
		m_fontsVitality.at(i)->setText(tmpString.substr(0, 3));
		m_fontsVitality.at(i)->setImagePath(cRenderingManager::getPathFont());
		m_fontsVitality.at(i)->setX((float)(72 + 80 * i));
		m_fontsVitality.at(i)->setY((float)(240 / 2 - 16 + 32));
		m_fontsVitality.at(i)->setIsHidden(true);

		m_iconsCoins.push_back(new cObject);
		m_iconsCoins.at(i)->loadConfig("Data\\Objects\\coin_8.cfg");
		m_iconsCoins.at(i)->setX((float)(64 + 80 * i));
		m_iconsCoins.at(i)->setY((float)(240 / 2 + 32));
		m_iconsCoins.at(i)->setIsHidden(true);

		m_iconsStamina.push_back(new cObject);
		m_iconsStamina.at(i)->loadConfig("Data\\Objects\\icon_8_stamina.cfg");
		m_iconsStamina.at(i)->setX((float)(64 + 80 * i));
		m_iconsStamina.at(i)->setY((float)(240 / 2 - 8 + 32));
		m_iconsStamina.at(i)->setIsHidden(true);

		m_iconsVitality.push_back(new cObject);
		m_iconsVitality.at(i)->loadConfig("Data\\Objects\\icon_8_vitality.cfg");
		m_iconsVitality.at(i)->setX((float)(64 + 80 * i));
		m_iconsVitality.at(i)->setY((float)(240 / 2 - 16 + 32));
		m_iconsVitality.at(i)->setIsHidden(true);

		m_fontsStamina.push_back(new cBitmapFont);
		m_fontsStamina.at(i)->setWidth(64);
		tmpString.clear();
		tmpString = std::to_string(cSavesManager::getPlayerStamina());
		m_fontsStamina.at(i)->setText(tmpString.substr(0, 3));
		m_fontsStamina.at(i)->setImagePath(cRenderingManager::getPathFont());
		m_fontsStamina.at(i)->setX((float)(72 + 80 * i));
		m_fontsStamina.at(i)->setY((float)(240 / 2 - 8 + 32));
		m_fontsStamina.at(i)->setIsHidden(true);

		m_fontsClear.push_back(new cBitmapFont);
		m_fontsClear.at(i)->setWidth(128);
		m_fontsClear.at(i)->setText("Clear");
		m_fontsClear.at(i)->setImagePath(cRenderingManager::getPathFont());
		m_fontsClear.at(i)->setX((float)(72 + 80 * i));
		m_fontsClear.at(i)->setY((float)(240 / 2 + 48));
		m_fontsClear.at(i)->setIsHidden(true);
	}
}

void cMenuState::setMenuIsHidden(unsigned short menuNumber, bool isHidden) {
	if (menuNumber == 0) {
		m_fontStart.setIsHidden(isHidden);
		m_fontOptions.setIsHidden(isHidden);
		m_fontExit.setIsHidden(isHidden);
	}
	else if (menuNumber == 1) {
		m_fontFullscreen.setIsHidden(isHidden);		m_fontFullscreenValue.setIsHidden(isHidden);
		m_fontWidescreen.setIsHidden(isHidden);		m_fontWidescreenValue.setIsHidden(isHidden);
		m_fontVsync.setIsHidden(isHidden);			m_fontVsyncValue.setIsHidden(isHidden);
		m_fontResolution.setIsHidden(isHidden);		m_fontResolutionValue.setIsHidden(isHidden);
		m_fontMusic.setIsHidden(isHidden);			m_fontMusicValue.setIsHidden(isHidden);
		m_fontMusicVolume.setIsHidden(isHidden);	m_fontMusicVolumeValue.setIsHidden(isHidden);
		m_fontJumpLock.setIsHidden(isHidden);		m_fontJumpLockValue.setIsHidden(isHidden);
		m_fontHoverLock.setIsHidden(isHidden);		m_fontHoverLockValue.setIsHidden(isHidden);
	}
	else if (menuNumber == 2) {
		for (unsigned char i = 0; i < 3; ++i) {
			m_fontsSlot.at(i)->setIsHidden(isHidden);
			m_fontsCoins.at(i)->setIsHidden(isHidden);
			m_iconsCoins.at(i)->setIsHidden(isHidden);
			m_iconsVitality.at(i)->setIsHidden(isHidden);
			m_iconsStamina.at(i)->setIsHidden(isHidden);
			m_fontsStamina.at(i)->setIsHidden(isHidden);
			m_fontsVitality.at(i)->setIsHidden(isHidden);
			m_fontsClear.at(i)->setIsHidden(isHidden);
		}
	}	
}

void cMenuState::setMenuItemsColor(unsigned char r, unsigned char g, unsigned char b) {
	for (unsigned char i = 0; i < 3; ++i) {
		m_fontsSlot.at(i)->setColor(r, g, b);
		m_fontsCoins.at(i)->setColor(r, g, b);
		m_iconsCoins.at(i)->setColor(r, g, b);
		m_iconsVitality.at(i)->setColor(r, g, b);
		m_iconsStamina.at(i)->setColor(r, g, b);
		m_fontsStamina.at(i)->setColor(r, g, b);
		m_fontsVitality.at(i)->setColor(r, g, b);
		m_fontsClear.at(i)->setColor(r, g, b);
	}
	m_fontArrow.setColor(r, g, b);
	m_fontStart.setColor(r, g, b);
	m_fontOptions.setColor(r, g, b);
	m_fontExit.setColor(r, g, b);
	m_fontFullscreen.setColor(r, g, b);		m_fontFullscreenValue.setColor(r, g, b);
	m_fontWidescreen.setColor(r, g, b);		m_fontWidescreenValue.setColor(r, g, b);
	m_fontVsync.setColor(r, g, b);			m_fontVsyncValue.setColor(r, g, b);
	m_fontResolution.setColor(r, g, b);		m_fontResolutionValue.setColor(r, g, b);
	m_fontMusic.setColor(r, g, b);			m_fontMusicValue.setColor(r, g, b);
	m_fontMusicVolume.setColor(r, g, b);	m_fontMusicVolumeValue.setColor(r, g, b);
	m_fontJumpLock.setColor(r, g, b);		m_fontJumpLockValue.setColor(r, g, b);
	m_fontHoverLock.setColor(r, g, b);		m_fontHoverLockValue.setColor(r, g, b);	
}

void cMenuState::updateMenuItems(cApp *app, float time) {
	m_fontArrow.update(time);
	m_fontStart.update(time);
	m_fontOptions.update(time);
	m_fontExit.update(time);

	m_fontFullscreen.update(time);
	m_fontFullscreenValue.update(time);
	m_fontWidescreen.update(time);
	m_fontWidescreenValue.update(time);
	m_fontVsync.update(time);
	m_fontVsyncValue.update(time);
	m_fontResolution.update(time);
	m_fontResolutionValue.update(time);
	m_fontMusic.update(time);
	m_fontMusicValue.update(time);
	m_fontMusicVolume.update(time);
	m_fontMusicVolumeValue.update(time);
	m_fontJumpLock.update(time);
	m_fontJumpLockValue.update(time);
	m_fontHoverLock.update(time);
	m_fontHoverLockValue.update(time);

	/*for (unsigned short y = 0; y < m_numMenuRows; ++y) {
		for (unsigned short x = 0; x < m_numMenuColumns; ++x) {
			m_menuObjects.at(x + y * m_numMenuColumns)->update(time);
		}
	}*/
	for (unsigned char i = 0; i < 3; ++i) {
		m_fontsSlot.at(i)->update(time);
		m_fontsCoins.at(i)->update(time);

		m_iconsVitality.at(i)->update(time);
		m_iconsCoins.at(i)->update(time);
		m_iconsStamina.at(i)->update(time);
		m_fontsStamina.at(i)->update(time);
		m_fontsVitality.at(i)->update(time);
		m_fontsClear.at(i)->update(time);
	}
}
