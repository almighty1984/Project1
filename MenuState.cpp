#include "InitPlayState.h"
#include "MenuState.h"
#include "App.h"

#include "CollisionManager.h"
#include "InputManager.h"
#include "MusicManager.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include "SoundsManager.h"

cMenuState::cMenuState() {
	init();	
}

cMenuState::cMenuState(cLevel *level) {
	m_levelPtr = level;
	init();
}

cMenuState::~cMenuState() {
	clear();
	if (m_levelPtr != nullptr) {
		delete m_levelPtr;
		m_levelPtr = nullptr;
	}
}

void cMenuState::exit(cApp *app) {
	std::cout << "cMenuState::exit() start" << "\n";
	if (this != nullptr) {
		delete this;
	}
	std::cout << "cMenuState::exit() end" << "\n";
}
void cMenuState::enter(cApp *app, cGameState *previousState) {
	app->setWeatherColor(0.0f);

	m_levelPtr->scrollX(64.0f);

	app->setUseEventInput(true);

	initTextBox();

	initObjects(app);

	int color = 0;
	m_fontFps.setColor(color, color, color);
	m_logo.setColor(color, color, color);
	m_levelPtr->setColor(color, color, color);
	setMenuItemsColor(color, color, color);

	stopWeather();	
	initWeather(app, m_levelPtr);

	std::cout << "cMenuState::enter() end" << "\n";
}

void cMenuState::update(cApp *app, float time) {
	if (app == nullptr || m_levelPtr == nullptr) {
		return;
	}
	int color = 0;
	if (!m_secondCall) {
		m_secondCall = true;
		m_screenColor = 0.0f;
		m_doFadeColorUp = true;
		m_doFadeColorDown = false;
		//app->setWeatherColor(0.0f);
		if (cRenderingManager::getIsWidescreen()) {
			m_widescreenOffset = 48.0f;
		} else {
			m_widescreenOffset = 0.0f;
		}

		
		
		//app->sleep(1);		
		
		m_levelPtr->update(app, time);

		updateMenuItems(app, time);		
	}

	m_timerState += time;
	// Darken weather?
	if (m_timerState > (400 + rand() % 400)) {
		m_timerState = 0.0f;
		m_doDarkenWeather = calculateWeather(app->getDarkenNumerator(), app->getDarkenDenominator());
		std::cout << "*m_doDarkenWeather = " << m_doDarkenWeather << "\n";
		m_doLightenWeather = calculateWeather(app->getLightenNumerator(), app->getLightenDenominator());
		std::cout << "*m_doLightenWeather = " << m_doLightenWeather << "\n";
	}
	updateWeather(app, m_levelPtr, time);
	updateMenuItems(app, time);
		
	if (m_doChangeColorWithWeather) {
		app->setWeatherColor(m_weatherColor);
		color = (int)m_weatherColor;
	} else {
		if (!m_doFadeColorUp && !m_doFadeColorDown) {
			color = 255;
		}
	}

	if (m_doFadeColorUp) {
		m_doFadeColorDown = false;
		m_screenColor += /*time * */10.0f;
		if (m_screenColor >= m_weatherColor) {
			m_screenColor = m_weatherColor;
			m_doFadeColorUp = false;
		}
		color = (int)m_screenColor;
		m_levelPtr->setIsLockedEntities(true);
	} else if (m_doFadeColorDown) {
		m_doFadeColorUp = false;
		m_screenColor -= /*time * */10.0f;
		if (m_screenColor <= 0.0f) {
			m_screenColor = 0.0f;
			m_doFadeColorDown = false;
		}
		color = (int)m_screenColor;
		m_levelPtr->setIsLockedEntities(true);
	}
	
	if (!m_doFadeColorDown && !m_doFadeColorUp) {
		m_levelPtr->setIsLockedEntities(false);
	}

	// Only update text if not the same as last frame
	if (m_prevFps != app->getFpsCurrent()) {
		m_prevFps = app->getFpsCurrent();
		m_strStream.clear();
		m_strStream.str("");
		m_strStream << app->getFpsCurrent();
		m_fontFps.setText(m_strStream.str().c_str());
		if (m_prevFps > 9999) {
			m_fontFps.setX(m_statusBarOffsetX + 304.0f + m_widescreenOffset * 1.25f - 24.0f);
		} else if (m_prevFps > 999 && m_prevFps <= 9999) {
			m_fontFps.setX(m_statusBarOffsetX + 304.0f + m_widescreenOffset * 1.25f - 16.0f);
		} else if (m_prevFps > 99 && m_prevFps <= 999) {
			m_fontFps.setX(m_statusBarOffsetX + 304.0f + m_widescreenOffset * 1.25f - 8.0f);
		} else {
			m_fontFps.setX(m_statusBarOffsetX + 304.0f + m_widescreenOffset * 1.25f);
		}
	}
	
	m_fontFps.setColor(color, color, color);

	m_textBox.setColor(color, color, color);

	m_logo.setColor(color, color, color);
	m_levelPtr->setColor(color, color, color);

	setMenuItemsColor(color, color, color);

	/*for (unsigned char i = 0; i < m_numScrollingTexts; ++i) {
		m_fontsCredits.at(i)->setColor(color, color, color);
		m_fontsCredits.at(i)->update(time);
		if (m_fontsCredits.at(i)->getX() < -48-m_fontsCredits.at(i)->getTextSize() * 8) {			
			if (i == 0) {
				m_fontsCredits.at(i)->setX(m_fontsCredits.at(m_numScrollingTexts-1)->getX() + (float)((160 + 48) + m_fontsCredits.at(m_numScrollingTexts-1)->getTextSize() * 8));
			} else {
				m_fontsCredits.at(i)->setX(m_fontsCredits.at(i-1)->getX() + (float)((160 + 48) + m_fontsCredits.at(i-1)->getTextSize() * 8));
			}			
		}
	}*/
	
	if (m_joyMovedCooldown > 0.0f) {
		m_joyMovedCooldown -= time;
	} else {
		m_joyMovedCooldown = 0.0f;
	}	

	//std::cout << "cMenuState::update() start" << "\n";
	cCollisionManager::update(app, nullptr, m_levelPtr, time);
	m_textBox.update(time);
	m_levelPtr->update(app, time);
	m_logo.update(time);
	m_fontFps.update(time);	
		
	if (m_menuNumber == 0) {
		setMenuIsHidden(0, false);
		setMenuIsHidden(1, true);
		setMenuIsHidden(2, true);
		if (keysHeld[sf::Keyboard::Up] ||
			(m_joyMovedY < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Up] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() > m_fontStart.getY()) {
				m_fontArrow.setY( m_fontArrow.getY() - 16 );
			}
		}
		if (keysHeld[sf::Keyboard::Down] ||
			(m_joyMovedY > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Down] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() < m_fontExit.getY()) {
				m_fontArrow.setY( m_fontArrow.getY() + 16 );
			}
		}
		if (keysHeld[sf::Keyboard::Return] || joyButtonsHeld[cInputManager::getJumpJoyButton()]) {
			keysHeld[sf::Keyboard::Return] = false;
			joyButtonsHeld[cInputManager::getJumpJoyButton()] = false;

			if (m_fontArrow.getY() == m_fontExit.getY()) {
				app->shutdown();
			} else if (m_fontArrow.getY() == m_fontOptions.getY()) {
				m_menuNumber = 1;
				m_fontArrow.setX(80.0f);
				m_fontArrow.setY(96.0f);
				setMenuIsHidden(0, true);
				setMenuIsHidden(1, false);
			} else {
				m_menuNumber = 2;
				m_fontArrow.setX(56.0f);
				m_fontArrow.setY(120.0f);
				
				setMenuIsHidden(0, true);
				setMenuIsHidden(2, false);
			}
		}
		if (keysHeld[sf::Keyboard::Escape]) {
			keysHeld[sf::Keyboard::Escape] = false;
			app->shutdown();
		}
	} else if (m_menuNumber == 1) {
		if (keysHeld[sf::Keyboard::Up] ||
			(m_joyMovedY < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Up] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() > m_fontFullscreen.getY()) {
				m_fontArrow.setY(m_fontArrow.getY() - 8);
			}
		}
		if (keysHeld[sf::Keyboard::Down] ||
			(m_joyMovedY > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Down] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() < m_fontHoverLock.getY()) {
				m_fontArrow.setY(m_fontArrow.getY() + 8);
			}
		}
		if (keysHeld[sf::Keyboard::Left] ||
			(m_joyMovedX < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Left] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() == m_fontFullscreen.getY()) {
				if (m_fontFullscreenValue.getText() == "true") {
					m_fontFullscreenValue.clearText();
					m_fontFullscreenValue.setText("false");
				}
			} else if (m_fontArrow.getY() == m_fontWidescreen.getY()) {
				if (m_fontWidescreenValue.getText() == "true") {
					m_fontWidescreenValue.clearText();
					m_fontWidescreenValue.setText("false");
				}
			} else if (m_fontArrow.getY() == m_fontVsync.getY()) {
				if (m_fontVsyncValue.getText() == "true") {
					m_fontVsyncValue.clearText();
					m_fontVsyncValue.setText("false");
				}
			} else if (m_fontArrow.getY() == m_fontResolution.getY()) {
				if (m_fontResolutionValue.getText() == "2x") {
					m_fontResolutionValue.clearText();
					m_fontResolutionValue.setText("1x");
				} else if (m_fontResolutionValue.getText() == "3x") {
					m_fontResolutionValue.clearText();
					m_fontResolutionValue.setText("2x");
				}
			} else if (m_fontArrow.getY() == m_fontMusic.getY()) {
				if (m_fontMusicValue.getText() == "true") {
					m_fontMusicValue.clearText();
					m_fontMusicValue.setText("false");
					cMusicManager::setDoPlay(false);
					cMusicManager::setDoLoop(0, true);
					cMusicManager::setMusic(0, app->getPathMusic(0));
					cMusicManager::setVolume(0, app->getMusicVolume());
					cMusicManager::stop(0);
				}
			} else if (m_fontArrow.getY() == m_fontMusicVolume.getY() && app->getMusicVolume() > 1.0f) {
				app->setMusicVolume(app->getMusicVolume() - 1.0f);
				cMusicManager::setVolume(0, app->getMusicVolume());
				m_fontMusicVolumeValue.clearText();
				m_fontMusicVolumeValue.setText(std::to_string((int)(app->getMusicVolume())));
			} else if (m_fontArrow.getY() == m_fontJumpLock.getY()) {
				if (m_fontJumpLockValue.getText() == "true") {
					m_fontJumpLockValue.clearText();
					m_fontJumpLockValue.setText("false");
				}
			} else if (m_fontArrow.getY() == m_fontHoverLock.getY()) {
				if (m_fontHoverLockValue.getText() == "true") {
					m_fontHoverLockValue.clearText();
					m_fontHoverLockValue.setText("false");
				}
			}
		}
		if (keysHeld[sf::Keyboard::Right] ||
			(m_joyMovedX > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Right] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() == m_fontFullscreen.getY()) {
				if (m_fontFullscreenValue.getText() == "false") {
					m_fontFullscreenValue.clearText();
					m_fontFullscreenValue.setText("true");
				}
			} else if (m_fontArrow.getY() == m_fontWidescreen.getY()) {
				if (m_fontWidescreenValue.getText() == "false") {
					m_fontWidescreenValue.clearText();
					m_fontWidescreenValue.setText("true");
				}
			} else if (m_fontArrow.getY() == m_fontVsync.getY()) {
				if (m_fontVsyncValue.getText() == "false") {
					m_fontVsyncValue.clearText();
					m_fontVsyncValue.setText("true");
				}
			} else if (m_fontArrow.getY() == m_fontResolution.getY()) {
				if (m_fontResolutionValue.getText() == "1x") {
					m_fontResolutionValue.clearText();
					m_fontResolutionValue.setText("2x");
				} else if (m_fontResolutionValue.getText() == "2x") {
					m_fontResolutionValue.clearText();
					m_fontResolutionValue.setText("3x");
				}
			} else if (m_fontArrow.getY() == m_fontMusic.getY()) {
				if (m_fontMusicValue.getText() == "false") {
					m_fontMusicValue.clearText();
					m_fontMusicValue.setText("true");
					cMusicManager::setDoPlay(true);
					cMusicManager::setDoLoop(0, true);
					cMusicManager::setMusic(0, app->getPathMusic(0));
					cMusicManager::setVolume(0, app->getMusicVolume());
					cMusicManager::play(0);
				}
			} else if (m_fontArrow.getY() == m_fontMusicVolume.getY() && app->getMusicVolume() < 100.0f) {
				app->setMusicVolume(app->getMusicVolume() + 1.0f);
				cMusicManager::setVolume(0, app->getMusicVolume());
				m_fontMusicVolumeValue.clearText();
				m_fontMusicVolumeValue.setText(std::to_string((int)(app->getMusicVolume())));
			} else if (m_fontArrow.getY() == m_fontJumpLock.getY()) {
				if (m_fontJumpLockValue.getText() == "false") {
					m_fontJumpLockValue.clearText();
					m_fontJumpLockValue.setText("true");
				}
			} else if (m_fontArrow.getY() == m_fontHoverLock.getY()) {
				if (m_fontHoverLockValue.getText() == "false") {
					m_fontHoverLockValue.clearText();
					m_fontHoverLockValue.setText("true");
				}
			}
		}
		if (keysHeld[sf::Keyboard::Return]) {
			keysHeld[sf::Keyboard::Return] = false;			
		}
		if (keysHeld[sf::Keyboard::Escape] || joyButtonsHeld[cInputManager::getMeleeJoyButton()]) {			
			keysHeld[sf::Keyboard::Escape] = false;
			joyButtonsHeld[cInputManager::getMeleeJoyButton()] = false;			
			m_menuNumber = 0;
			m_fontArrow.setX(136 - 16);
			m_fontArrow.setY(56.0f);
			
			setMenuIsHidden(0, false);
			setMenuIsHidden(1, true);

			if (m_fontFullscreenValue.getText() == "false") {
				app->setIsFullscreen(false);
			} else {
				app->setIsFullscreen(true);
			}
			if (m_fontWidescreenValue.getText() == "false") {
				app->setIsWidescreen(false);
			} else {
				app->setIsWidescreen(true);
			}
			if (m_fontVsyncValue.getText() == "false") {
				app->setUseVerticalSync(false);
			} else {
				app->setUseVerticalSync(true);
			}			
			if (m_fontResolutionValue.getText() == "1x") {
				app->setWindowMultiplier(1.0f);
			} else if (m_fontResolutionValue.getText() == "2x") {
				app->setWindowMultiplier(2.0f);
			} else if (m_fontResolutionValue.getText() == "3x") {
				app->setWindowMultiplier(3.0f);
			}
			if (m_fontJumpLockValue.getText() == "false") {
				app->setUseJumpLock(false);
			} else {
				app->setUseJumpLock(true);
			}
			if (m_fontHoverLockValue.getText() == "false") {
				app->setUseHoverLock(false);
			} else {
				app->setUseHoverLock(true);
			}
			app->writeConfigBinary();
			delete this;
			
			app->shutdown();
			app->init(app);
			app->run(app);
			return;
		}
	}
	else if (m_menuNumber == 2) {
		if (keysHeld[sf::Keyboard::Left] ||
			 (m_joyMovedX < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Left] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getX() > 56) {
				m_fontArrow.setX(m_fontArrow.getX() - 80);
				--m_slotNumber;
				std::cout << "Slot " << (int)m_slotNumber << "\n";
			} else {
				m_slotNumber = 0;
			}
		}
		if (keysHeld[sf::Keyboard::Right] ||
			(m_joyMovedX > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Right] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getX() < 216) {
				m_fontArrow.setX(m_fontArrow.getX() + 80);
				++m_slotNumber;
				std::cout << "Slot " << (int)m_slotNumber << "\n";
			} else {
				m_slotNumber = 2;
			}
		}
		if (keysHeld[sf::Keyboard::Up] ||
			(m_joyMovedY < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Up] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() > 240 / 2) {
				m_fontArrow.setY(240 / 2);
			}
		}
		if (keysHeld[sf::Keyboard::Down] ||
			(m_joyMovedY > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
			keysHeld[sf::Keyboard::Down] = false;
			m_joyMovedCooldown = 20.0f;
			if (m_fontArrow.getY() < 240 / 2 + 48) {
				m_fontArrow.setY(240 / 2 + 48);
			}
		}
		if (keysHeld[sf::Keyboard::Return] || joyButtonsHeld[cInputManager::getJumpJoyButton()]) {
			keysHeld[sf::Keyboard::Return] = false;
			joyButtonsHeld[cInputManager::getJumpJoyButton()] = false;
			
			if (m_fontArrow.getY() == 240/2) {
				m_menuNumber = 3;
				m_fontsSlot.at(m_slotNumber)->setText(m_fontsSlot.at(m_slotNumber)->getText() + "_");
			}
			else if (m_fontArrow.getY() == 240/2+48) {
				cSavesManager::clearAll();
				cSavesManager::initSave();
				cSavesManager::setSlotNumber(m_slotNumber);
				cSavesManager::writeSave(true, true, true);

				initMenuItems(app);

				std::cout << "m_slotNumber = " << (int)m_slotNumber << "\n";				

				//m_textBox.loadConfig("Data\\TextBoxes\\menu.cfg");
				
				//m_textBox.setText("  Slot " + std::to_string(m_slotNumber) + " cleared");
				initTextBox();
				m_textBox.setTextFromKey("clear");

				std::cout << m_textBox.getTextFromKey("clear") << "\n";

				m_textBox.setTimerHide(60);
				m_fontArrow.setY(240 / 2);

				setMenuIsHidden(2, false);
			}		
			
		}
		if (keysHeld[sf::Keyboard::Escape] || joyButtonsHeld[cInputManager::getMeleeJoyButton()]) {
			keysHeld[sf::Keyboard::Escape] = false;
			joyButtonsHeld[cInputManager::getMeleeJoyButton()] = false;
			m_menuNumber = 0;
			m_fontArrow.setX(136 - 16);
			m_fontArrow.setY(120.0f);
			setMenuIsHidden(0, false);
			setMenuIsHidden(2, true);
		}		
	} else if (m_menuNumber == 3 && !m_doBeginPlayState) {
		std::string s;
		if (m_fontsSlot.at(m_slotNumber)->getText().size() < 8) {
			bool pressedShift = false;
			keysHeld[sf::Keyboard::LShift] ? pressedShift = true : pressedShift = false;
			// Go through letters of the alphabet
			for (int i = 0; i < 26; ++i) {
				if (keysHeld[i]) {
					keysHeld[i] = false;
					pressedShift ? s = m_alphabet[i+26] : s = m_alphabet[i];
					s.append("_");
					m_fontsSlot.at(m_slotNumber)->setText(m_fontsSlot.at(m_slotNumber)->getText().substr(0, m_fontsSlot.at(m_slotNumber)->getText().size() - 1) + s);
				}
			}			
		}
		if (keysHeld[sf::Keyboard::BackSpace]) {
			keysHeld[sf::Keyboard::BackSpace] = false;
			m_fontsSlot.at(m_slotNumber)->setText(m_fontsSlot.at(m_slotNumber)->getText().substr(0, m_fontsSlot.at(m_slotNumber)->getText().size() - 2));

			if (m_fontsSlot.at(m_slotNumber)->getText() != "_") {
				m_fontsSlot.at(m_slotNumber)->setText(m_fontsSlot.at(m_slotNumber)->getText() + "_");
			}
		}
		if (keysHeld[sf::Keyboard::Return] || joyButtonsHeld[cInputManager::getJumpJoyButton()]) {
			keysHeld[sf::Keyboard::Return] = false;
			joyButtonsHeld[cInputManager::getJumpJoyButton()] = false;

			if (m_fontArrow.getY() == 240 / 2 && m_fontsSlot.at(m_slotNumber)->getText() != "_") {

				m_fontsSlot.at(m_slotNumber)->setText(m_fontsSlot.at(m_slotNumber)->getText().substr(0, m_fontsSlot.at(m_slotNumber)->getText().size()-1));
					
				//if (m_fontArrow.getX() == m_fontSlotFirst.getX()) {
				m_logo.setIsDead(true);
				m_logo.setTileOffsetX(0.0f);
				m_doBeginPlayState = true;
				m_timerState = 0;
				//}
			}
		}

		if (keysHeld[sf::Keyboard::Escape] || joyButtonsHeld[cInputManager::getMeleeJoyButton()]) {
			keysHeld[sf::Keyboard::Escape] = false;
			joyButtonsHeld[cInputManager::getMeleeJoyButton()] = false;
			m_menuNumber = 2;
			m_fontsSlot.at(m_slotNumber)->setText(m_fontsSlot.at(m_slotNumber)->getText().substr(0, m_fontsSlot.at(m_slotNumber)->getText().size() - 1));
		}		
	}

	if (keysHeld[sf::Keyboard::G]) {
		keysHeld[sf::Keyboard::G] = false;
		cRenderingManager::setShowLevelNodeGrid(!cRenderingManager::getShowLevelNodeGrid());
	}
	
	if (m_doBeginPlayState) {		
		m_doFadeColorDown = true;
		m_doChangeColorWithWeather = false;
		if (m_screenColor <= 0.0f) {
			m_doChangeColorWithWeather = true;
			m_doFadeColorDown = false;
			m_doBeginPlayState = false;
			/*m_timerState += time;
			if (m_timerState > 100) {
				m_doBeginPlayState = false;*/
				m_pathLevel = "Data\\Levels\\5000_5000.bin";
				m_playerStart = "center";
				m_strStream.clear();
				m_strStream.str("");
				m_strStream << (int)m_slotNumber;
				cSavesManager::clearAll();
				cSavesManager::setSlotNumber(m_slotNumber);
				//cSavesManager::initSave();
				cSavesManager::readSave("Data\\Saves\\" + m_strStream.str() + ".bin");
				cSavesManager::setPlayerName(m_fontsSlot.at(m_slotNumber)->getText());
				m_pathLevel = cSavesManager::getPathLevel();
				cSavesManager::setCurrentLevel(m_pathLevel);

				std::cout << m_fontsSlot.at(m_slotNumber)->getText() << "\n";

				// Write save with new name
				cSavesManager::writeSave(cSavesManager::getHasHover(), cSavesManager::getHasSprint(), cSavesManager::getHasWhirl());

				//std::cout << "PATHLEVEL!!!!!!!!!!!!!!!!!!!!!!!!!!!" << cSavesManager::getPathLevel();
				//app->sleep(5000);
				//cSavesManager::setNumHealth(99);

				sStartInfo startInfo;
				startInfo.start = m_playerStart;
				startInfo.state = m_playerState;

				app->setState(new cInitPlayState(m_pathLevel, startInfo));

				/*delete this;
				std::cout << "DELETED MENUSTATE NOW!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";*/
				return;
			//}
		}
	}
}

void cMenuState::render(cApp *app){
	/*for (unsigned char i = 0; i < m_level.getNumBackgrounds(); ++i) {
		cRenderingManager::renderBackgrounds(i, app);
	}*/
	cRenderingManager::renderBackgroundPlanes(app);
	
	cRenderingManager::renderLevel(0, app);
	cRenderingManager::renderEntities(0, app);
	cRenderingManager::renderLevel(1, app);
	cRenderingManager::renderEntities(1, app);
	cRenderingManager::renderLevel(2, app);
	cRenderingManager::renderEntities(2, app);
	cRenderingManager::renderLevel(3, app);
	cRenderingManager::renderEntities(3, app);
	cRenderingManager::renderLevel(4, app);
	cRenderingManager::renderEntities(4, app);
	cRenderingManager::renderObjects(app);


	//if (!m_doHideForeground) {
		cRenderingManager::renderForegroundPlanes(app);
	//}

	//cRenderingManager::renderForegrounds(0, app);
	//cRenderingManager::renderForegrounds(1, app);
	cRenderingManager::renderBitmapFonts(app);
	cRenderingManager::renderParticles(app);
	//cRenderingManager::renderQuadNodes(app);
}