#include "InitMenuState.h"
#include "InitPlayState.h"

#include "PlayState.h"
#include "App.h"
#include "InputManager.h"
//#include "JoystickManager.h"
#include "RenderingManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"

#include "MusicManager.h"

#include "SavesManager.h"
#include "MapsManager.h"
#include "SoundsManager.h"

#include "Player.h"
#include "PlayerGrassState.h"
#include "PlayerWaterState.h"
#include "PlayerShopState.h"

#include <SFML/Window.hpp>

//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>

cPlayState::cPlayState() {
	m_pathLevel = "Data\\Levels\\5000_5000.bin";
	sStartInfo startInfo;
	startInfo.start = "center";
	startInfo.state = "grass";
	init(m_pathLevel, startInfo);
}

cPlayState::cPlayState(cLevel* level, std::string levelPath, sStartInfo startInfo) {
	init(levelPath, startInfo);
	m_levelPtr = level;
}

void cPlayState::init(const std::string& pathLevel, sStartInfo startInfo) {
	std::cout << "PlayState init\n";
	m_pathLevel = pathLevel;
	m_playerStart = startInfo.start;
	m_playerState = startInfo.state;
	m_player1.setIsFacingLeft(startInfo.facingLeft);
	m_player1.setVelocityX(startInfo.velocityX);
	m_doStartUnlocked = startInfo.startUnlocked;
	//cRenderingManager::setIsViewLocked(true);
	m_timerState = 0;
	m_secondCall = false;
	m_statusBarOffsetX = 0.0f;
	m_doQuitToMenu = false;
	m_doUseWeather = false;
	m_doChangeLevel = false;
	m_doChangeColorWithWeather = false;
	m_doDarkenWeather = false;
	m_doLightenWeather = false;
	m_activatedTextSign = false;
	m_inExitMenu = false;
	m_activatedTextSign = false;
	m_tileX, m_tileY = m_entityTileX = m_entityTileY = m_prevNumCoins = 0;

	m_weatherColor = 255.0f;
	m_screenColor = 0.0f;
	m_velocityX = 0.0f;
	if (cRenderingManager::getIsWidescreen()) {
		m_widescreenOffset = 48.0f;
	} else {
		m_widescreenOffset = 0.0f;
	}

	m_joyMovedCooldown = 20.0f;
	
	m_fontFps.setY(0.0f);
	m_fontFps.clearText();
	m_fontFps.setWidth(64);
	//m_fontFps.setUseFloatPosition(true);

	m_iconCoins.loadConfig("Data\\Objects\\coin_8.cfg");
	m_iconCoins.setX(m_statusBarOffsetX - m_widescreenOffset);
	m_iconCoins.setY(0.0f);

	m_fontCoins.setX(m_statusBarOffsetX + 8.0f - m_widescreenOffset);
	m_fontCoins.setY(0.0f);
	m_fontCoins.clearText();
	m_fontCoins.setWidth(48);

	m_meterVitalityBackground.setImagePath("Data\\Objects\\Images\\meter_vitality_bg.png");
	m_meterVitalityBackground.setX(m_statusBarOffsetX + 80.0f);
	m_meterVitalityBackground.setY(0.0f);
	m_meterVitalityBackground.setWidth(64);
	m_meterVitalityBackground.setHeight(8);
	m_meterVitality.setImagePath("Data\\Objects\\Images\\meter_vitality.png");
	m_meterVitality.setX(m_statusBarOffsetX + 80.0f);
	m_meterVitality.setY(0.0f);
	m_meterVitality.setWidth(64);
	m_meterVitality.setHeight(8);

	m_fontVitality.setX(m_statusBarOffsetX + 144.0f);
	m_fontVitality.setY(0.0f);
	m_fontVitality.clearText();
	m_fontVitality.setWidth(48);

	m_fontStamina.setX(m_statusBarOffsetX + 240.0f);
	m_fontStamina.setY(0.0f);
	m_fontStamina.clearText();
	m_fontStamina.setWidth(48);

	m_meterStaminaBackground.setImagePath("Data\\Objects\\Images\\meter_stamina_bg.png");
	m_meterStaminaBackground.setX(m_statusBarOffsetX + 176.0f);
	m_meterStaminaBackground.setY(0.0f);
	m_meterStaminaBackground.setWidth(64);
	m_meterStaminaBackground.setHeight(8);
	m_meterStamina.setImagePath("Data\\Objects\\Images\\meter_stamina.png");
	m_meterStamina.setX(m_statusBarOffsetX + 176.0f);
	m_meterStamina.setY(0.0f);
	m_meterStamina.setWidth(64);
	m_meterStamina.setHeight(8);


	m_textBox.loadConfig("Data\\TextBoxes\\" + pathLevel.substr(12, 9) + ".cfg");
	m_textBox.setupBoxObjects(10, 2);

	m_textBox.setX(80);
	m_textBox.setY(204);
	m_textBox.setIsHidden(true);
}
cPlayState::~cPlayState() {
	std::cout << "~cPlayState()\n";

	m_player1.setNextLevel("");

	cMapsManager::clearMaps();

	cRenderingManager::clearBackgroundPlanes();
	cRenderingManager::clearForegroundPlanes();
	cRenderingManager::clearPlayers();
	cRenderingManager::clearBitmapFonts();
	cRenderingManager::clearParticles();
	cRenderingManager::clearLevel();

	cInputManager::detachListener(&m_player1);

	if (m_levelPtr != nullptr) {
		delete m_levelPtr;
		m_levelPtr = nullptr;
	}
}

void cPlayState::exit(cApp* app) {
	std::cout << "cPlayState::exit() start\n";
	if (this != nullptr) {
		delete this;
	}
	std::cout << "cPlayState::exit() end\n";
}

void cPlayState::enter(cApp* app, cGameState* previousState) {
	cMusicManager::setDoLoop(0, true);

	m_timerState = app->getTimerState();

	std::cout << "cPlayState()::enter\n";
	m_player1.loadConfig(app->getPathPlayer1());

	std::cout << "m_playerState = " << m_playerState << "\n";
	if (m_playerState == "water") {
		m_player1.setState(new cPlayerWaterState);
	} else if (m_playerState == "shop") {
		m_player1.setState(new cPlayerShopState);
	} else {
		m_player1.setState(new cPlayerGrassState);
	}

	m_player1.setCurrentLevel(m_pathLevel);
	cSavesManager::setCurrentLevel(m_pathLevel);

	m_player1.setStrength(cSavesManager::getPlayerStrength());
	m_player1.setVitality(cSavesManager::getPlayerVitality());
	m_player1.setStamina(cSavesManager::getPlayerStamina());
	m_player1.setStaminaMeterValue(cSavesManager::getStaminaMeterValue());
	m_player1.setVitalityMeterValue(cSavesManager::getVitalityMeterValue());

	std::stringstream stringStream;

	if (cSavesManager::getPlayerVitality() == 1.0f) {
		m_fontVitality.setText("1.0");
	} else if (cSavesManager::getPlayerVitality() == 2.0f) {
		m_fontVitality.setText("2.0");
	} else {
		stringStream << cSavesManager::getPlayerVitality();
		m_fontVitality.setText(stringStream.str());
	}

	stringStream.clear();

	if (cSavesManager::getPlayerStamina() == 1.0f) {
		m_fontStamina.setText("1.0");
	} else if (cSavesManager::getPlayerStamina() == 2.0f) {
		m_fontStamina.setText("2.0");
	} else {
		stringStream << cSavesManager::getPlayerStamina();
		m_fontStamina.setText(std::to_string(cSavesManager::getPlayerStamina()));
	}

	m_prevFps = app->getFpsCurrent();

	stringStream.clear();
	stringStream << app->getFpsCurrent();
	m_fontFps.setText(stringStream.str());

	m_prevNumCoins = cSavesManager::getNumCoins();
	m_fontCoins.setText(std::to_string(cSavesManager::getNumCoins()));

	m_levelPtr->attachPlayer(&m_player1);
	m_player1.attachLevel(m_levelPtr);

	initPlayerStart(app);
	initWeather(app, m_levelPtr);
	cSavesManager::addMap(m_pathLevel);

	cRenderingManager::addPlayer(&m_player1);
	cRenderingManager::addLevel(m_levelPtr);
	cRenderingManager::attachLevel(m_levelPtr);
	cRenderingManager::addBitmapFont(&m_fontCoins);
	cRenderingManager::addBitmapFont(&m_fontFps);
	cRenderingManager::addBitmapFont(&m_fontVitality);
	cRenderingManager::addBitmapFont(&m_fontStamina);
	cRenderingManager::addObject(&m_meterVitalityBackground);
	cRenderingManager::addObject(&m_meterStaminaBackground);
	cRenderingManager::addObject(&m_meterVitality);
	cRenderingManager::addObject(&m_meterStamina);
	cRenderingManager::addObject(&m_iconCoins);

	cInputManager::attachListener(&m_player1);

	cMapsManager::init(app);

	std::cout << "cPlayState::enter finished\n";
}

void cPlayState::update(cApp* app, float time) {
	if (app == nullptr || m_levelPtr == nullptr) {
		std::cout << "PlayState::update not initialized\n";
		app->sleep(10000);
		return;
	}

	if (!m_secondCall) {
		//app->setDoUpdateEveryFrame(false);
		std::cout << "cPlayState::update\n";
		m_secondCall = true;
		m_doFadeColorUp = true;
		m_doFadeColorDown = false;
		m_timerState = 0.0f;

		//std::cout << " cPlayState::update " << "Player position: " << " " << m_player1.getX() << " " << m_player1.getY() << "\n";
		m_screenColor = 0.0f;
		m_prevNumCoins = cSavesManager::getNumCoins();
	}

	if (!m_inExitMenu/* && !m_player1.getIsInMap()*/) {
		if (cMusicManager::getDoPlay()) {
			if (!cMusicManager::isPlaying(0)) {
				cMusicManager::play(0);
				cMusicManager::play(1);
			}
			if (m_player1.getDoPlayMusic(0)) {
				if (app->getMusicVolume() != cMusicManager::getVolume(0)) {
					//cMusicManager::setMusicBackground(app->getPathMusic0());
					//cMusicManager::setMusicBackgroundOffset( cMusicManager::getMusicBackgroundOffset() );
					//cMusicManager::playMusicBackground();
					cMusicManager::setVolume(0, app->getMusicVolume());
					cMusicManager::setVolume(1, 0.0f);
				}
			} else if (m_player1.getDoPlayMusic(1)) {
				if (app->getMusicVolume() != cMusicManager::getVolume(1)) {
					//cMusicManager::setMusicBackground(app->getPathMusic1());
					//cMusicManager::setMusicBackgroundOffset( cMusicManager::getMusicBackgroundOffset() );
					//cMusicManager::playMusicBackground();
					cMusicManager::setVolume(0, 0.0f);
					cMusicManager::setVolume(1, app->getMusicVolume());
				}
			}
		}
	}
	if (m_player1.getIsDead() && !m_inExitMenu && !m_player1.getIsInMap() && (cMusicManager::isPlaying(0) || cMusicManager::isPlaying(1))) {
		cMusicManager::stop(0);
		cMusicManager::stop(1);
	}

	int color = 0;
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
		m_screenColor += time * 10.0f;
		if (m_screenColor > m_weatherColor) {
			m_screenColor = m_weatherColor;
			m_doFadeColorUp = false;
		}
		color = (int)m_screenColor;
	} else if (m_doFadeColorDown) {
		m_doFadeColorUp = false;
		m_screenColor -= time * 10.0f;
		if (m_screenColor <= 0.0f) {
			m_screenColor = 0.0f;
		}
		color = (int)m_screenColor;
	}

	//std::cout << m_doFadeColorDown << " " << m_doFadeColorUp << "\n";

	m_levelPtr->setColor(color, color, color);
	m_player1.setColor(color, color, color);
	m_textBox.setColor(color, color, color);

	if (m_player1.getIsInMap() || m_player1.getIsInShop() || m_player1.getIsInWater()) {
		app->setUseEventInput(true);
	} else {
		app->setUseEventInput(false);
	}

	// PlayState player is dead, done with Super Mario death
	if (m_player1.getTimeBeingDead() >= m_player1.getTimeToBeDead() && m_secondCall) {
		std::cout << "PlayState player is dead, done with Super Mario death" << "\n";

		cSavesManager::clearAll();
		//cSavesManager::initSave();

		std::stringstream stringStream;
		stringStream << (int)cSavesManager::getSlotNumber();

		cSavesManager::readSave("Data\\Saves\\" + stringStream.str() + ".bin");
		/*cMusicManager::setVolume(0, app->getMusicVolume());
		cMusicManager::setDoLoopMusic(0, true);
		cMusicManager::setVolume(1, 0.0f);
		cMusicManager::setDoLoopMusic(1, true);*/

		sStartInfo startInfo;
		startInfo.start = "center";
		startInfo.state = "grass";

		app->setState(new cInitPlayState(cSavesManager::getPathLevel(), startInfo));
		//delete this;
		return;
	}

	// Game paused
	if (m_inExitMenu || app->getIsLocked()) {
		if (cSoundsManager::isPlaying(eSoundTag::rainOut)) {
			cSoundsManager::pause(eSoundTag::rainOut);
		}
		float loweredVolume = floor(app->getMusicVolume() / 3);
		//std::cout << loweredVolume << "\n";

		if (m_player1.getIsInWater()) {
			cMusicManager::setVolume(1, loweredVolume);
		} else {
			cMusicManager::setVolume(0, loweredVolume);
		}
	} else {
		if (!cSoundsManager::isPlaying(eSoundTag::rainOut) && app->getWeatherType() == 0) {
			cSoundsManager::play(eSoundTag::rainOut);
		}

		if (m_player1.getIsInWater()) {
			cMusicManager::setVolume(1, app->getMusicVolume());
		} else {
			cMusicManager::setVolume(0, app->getMusicVolume());
		}
	}

	if (m_player1.getIsInMap()) {
		app->setUseEventInput(true);
		cMapsManager::setIsHidden(false);
		if (getIsPressingUp() && m_joyMovedCooldown == 0.0f) {
			setIsPressingUp(false);
			m_joyMovedCooldown = 10.0f;
			cMapsManager::setY(cMapsManager::getY() - 16);
			std::cout << "cPlayState::update cMapsManager::getY() " << cMapsManager::getY() << "\n";
		}
		if (getIsPressingDown() && m_joyMovedCooldown == 0.0f) {
			setIsPressingDown(false);
			m_joyMovedCooldown = 10.0f;
			cMapsManager::setY(cMapsManager::getY() + 16);
			std::cout << "cPlayState::update cMapsManager::getY() " << cMapsManager::getY() << "\n";
		}
		if (getIsPressingLeft() && m_joyMovedCooldown == 0.0f) {
			setIsPressingLeft(false);
			m_joyMovedCooldown = 10.0f;
			cMapsManager::setX(cMapsManager::getX() - 16);
			std::cout << "cPlayState::update cMapsManager::getX() " << cMapsManager::getX() << "\n";
		}
		if (getIsPressingRight() && m_joyMovedCooldown == 0.0f) {
			setIsPressingRight(false);
			m_joyMovedCooldown = 10.0f;
			cMapsManager::setX(cMapsManager::getX() + 16);
			std::cout << "cPlayState::update cMapsManager::getX() " << cMapsManager::getX() << "\n";
		}
	} else {
		cMapsManager::setIsHidden(true);
	}
	if (!m_player1.getIsNearSign() && !m_inExitMenu && !m_player1.getIsInMap() && !m_player1.getIsInWater()) {
		app->setUseEventInput(false);
		m_textBox.setIsHidden(true);
		m_activatedTextSign = false;
	}
	/*if (m_player1.getIsNearSign() || m_player1.getIsNearShop() || m_player1.getIsNearDoor() || m_player1.getIsInWater()) {
		app->setUseEventInput(true);
	}*/

	//std::cout << "PlayState::update " << m_timerState << "\n";

	if (getIsPressingUp() && !m_player1.getIsLockedOpen() && !m_player1.getIsInWater() && !m_player1.getIsInMap() && !m_player1.getIsInShop() && !app->getIsLocked()) {
		setIsPressingUp(false);
		m_joyMovedCooldown = 10.0f;

		//std::cout << "PlayState Pressed UP" << "\n";
		if (m_player1.getIsNearSign() && !m_player1.getIsCarrying()) {
			for (unsigned char i = 0; i < 4; ++i) {
				if (m_player1.getIsInSign(i) && !m_player1.getIsInMap()) {

					m_activatedTextSign = !m_activatedTextSign;
					m_inExitMenu = false;

					m_player1.setIsLockedOpen(true);

					if (m_activatedTextSign) {						
						//m_textBox.clear();
						m_textBox.setupBoxObjects(16, 5);
						m_textBox.setX(40);
						m_textBox.setY(160);

						std::stringstream stringStream;
						stringStream << (int)i;

						m_textBox.setText(m_textBox.getTextFromKey("sign" + stringStream.str()));
						//m_textBox.setText(app->getPathTextBox(i));
						m_textBox.setColor(color, color, color);
					}

					//std::cout << i << " " << m_activatedTextSign << "\n";
					break;
				}
			}
		}
	}
	if (!m_inExitMenu && !app->getIsLocked()) {
		m_player1.update(app, time);
		if (m_player1.getTimeBeingDead() < 1.0f) {
			m_levelPtr->update(app, time);
		}
	}
	if (m_player1.getIsInWater()) {
		m_activatedTextSign = false;
		m_player1.setIsNearSign(false);
	}

	if (keysHeld[sf::Keyboard::G]) {
		keysHeld[sf::Keyboard::G] = false;
		cRenderingManager::setShowLevelNodeGrid(!cRenderingManager::getShowLevelNodeGrid());
	}

	if (keysHeld[sf::Keyboard::Return] && !m_player1.getIsInShop() && !m_inExitMenu) {
		keysHeld[sf::Keyboard::Return] = false;
		m_activatedTextSign = false;

		if (cMapsManager::getIsHidden()) {
			cMapsManager::setIsHidden(false);
			m_player1.setIsInMap(true);
		} else {
			cMapsManager::setIsHidden(true);
			m_player1.setIsInMap(false);
		}
	}

	if (app->getIsLocked() && m_textBox.getText().empty()) {
		m_textBox.clearText();
		//m_textBox.clear();
		//m_textBox.loadConfig("Data\\TextBoxes\\" + m_pathLevel.substr(12, 9) + ".cfg");
		
		m_textBox.setupBoxObjects(7, 2);
		m_textBox.setX(104);
		m_textBox.setY(96);
		m_textBox.setText("Game paused.");
		m_textBox.setColor(color, color, color);
		m_textBox.update(time);
	}

	if (keysHeld[sf::Keyboard::Escape] || keysHeld[sf::Keyboard::F12] && !app->getIsLocked()) {
		std::cout << "Pressed Esc" << "\n";
		keysHeld[sf::Keyboard::Escape] = false;
		keysHeld[sf::Keyboard::F12] = false;
		//if(cMusicManager::getDoPlayMusic() == true) {
			//cMusicManager::stopMusicBackground();
		//}
		m_inExitMenu = !m_inExitMenu;
		m_textBox.clearText();
		if (m_inExitMenu) {
			m_player1.setIsInMap(false);
			cMapsManager::setIsHidden(true);
			m_activatedTextSign = false;
			//m_textBox.clear();			
			//m_textBox.loadConfig("Data\\TextBoxes\\" + m_pathLevel.substr(12, 9) + ".cfg");
			
			m_textBox.setupBoxObjects(7, 2);
			m_textBox.setX(104);
			m_textBox.setY(96);
			m_textBox.setText("Quit?  (Y/N)");
			m_textBox.setColor(color, color, color);
		}
	}
	//std::cout << "m_timerState = " << m_timerState << "\n";
	//cGlobals::get().m_quadNode.update(time);
	if (!m_player1.getIsInMap() && !m_inExitMenu && !m_player1.getIsDead()/* && m_screenColor >= m_weatherColor*/) {
		m_timerState += time;

		// Darken weather?
		if (m_timerState > (400 + rand() % 400)) {
			m_timerState = 0.0f;
			m_doDarkenWeather = calculateWeather(app->getDarkenNumerator(), app->getDarkenDenominator());
			std::cout << "*cPlayState m_doDarkenWeather = " << m_doDarkenWeather << "\n";
			m_doLightenWeather = calculateWeather(app->getLightenNumerator(), app->getLightenDenominator());
			std::cout << "*cPlayState m_doLightenWeather = " << m_doLightenWeather << "\n";
		}
		updateWeather(app, m_levelPtr, time);

		//m_level.setColor(color, color, color);
		m_levelPtr->setColor(color, color, color);
		m_player1.setColor(color, color, color);
		m_fontVitality.setColor(color, color, color);
		m_fontStamina.setColor(color, color, color);
		m_fontFps.setColor(color, color, color);
		m_meterVitality.setColor(color, color, color);
		m_meterStamina.setColor(color, color, color);
		m_meterVitalityBackground.setColor(color, color, color);
		m_meterStaminaBackground.setColor(color, color, color);
		m_textBox.setColor(color, color, color);
		m_iconCoins.setColor(color, color, color);
		//cMapsManager::setColor(color, color, color);		
	}

	// Only update text if not the same as last frame
	if (m_prevFps != app->getFpsCurrent() && !app->getIsLocked()) {
		m_prevFps = app->getFpsCurrent();
		std::stringstream stringStream;
		stringStream << app->getFpsCurrent();
		m_fontFps.setText(stringStream.str());
		//std::cout << m_prevFps / 100 << "\n";

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

	if (m_prevNumCoins != cSavesManager::getNumCoins() && !app->getIsLocked()) {
		m_prevNumCoins = cSavesManager::getNumCoins();
		std::stringstream stringStream;
		stringStream << cSavesManager::getNumCoins();
		m_fontCoins.setText(stringStream.str());
	}
	m_fontFps.setColor(color, color, color);
	m_fontCoins.setColor(color, color, color);

	m_fontFps.update(time);
	m_fontCoins.update(time);

	m_meterVitality.setWidth((int)m_player1.getVitalityMeterValue());
	m_meterStamina.setWidth((int)m_player1.getStaminaMeterValue());

	m_fontVitality.update(time);
	m_fontStamina.update(time);
	m_meterVitality.update(time);
	m_meterStamina.update(time);
	m_meterVitalityBackground.update(time);
	m_meterStaminaBackground.update(time);
	m_textBox.update(time);
	m_iconCoins.update(time);

	cMapsManager::update(app, m_levelPtr, time);
	cCollisionManager::update(app, &m_player1, m_levelPtr, time);
	cCameraManager::update(app, m_levelPtr, &m_player1, time);


	if (m_joyMovedCooldown > 0.0f) {
		m_joyMovedCooldown -= time;
	} else {
		m_joyMovedCooldown = 0.0f;
	}

	if (m_hasMouseMoved) {
		//std::cout << "new mouse x: " << m_mouseX << "\n";
		//std::cout << "new mouse y: " << m_mouseY << "\n";
	}
	if (m_inExitMenu || m_activatedTextSign || app->getIsLocked()) {
		if (m_textBox.getIsHidden()) {
			m_textBox.setIsHidden(false);
		}
	} else {
		if (!m_textBox.getIsHidden()) {
			m_textBox.setIsHidden(true);
		}
	}

	if (m_inExitMenu && m_secondCall) {
		app->setIsPaused(true);
		if (keysHeld[sf::Keyboard::N]) {
			keysHeld[sf::Keyboard::N] = false;
			m_inExitMenu = false;
			m_secondCall = false;
			//m_player1.setShowTextBox(false);
		} else if (keysHeld[sf::Keyboard::Y]) {
			keysHeld[sf::Keyboard::Y] = false;
			if (m_inExitMenu) {
				m_doQuitToMenu = true;
			}
		}
	} else {
		app->setIsPaused(false);
	}

	if (m_doQuitToMenu) {
		m_doFadeColorDown = true;
		if (m_screenColor <= 0.0f) {
			//cSavesManager::clearAll();
			app->setState(new cInitMenuState);
			//delete this;
			return;
		}
	}

	//std::cout << "PlayState::update " << m_player1.getX() << "\n";

	if (!m_doFadeColorDown && checkChangeLevel(app, m_player1, m_pathLevel, m_playerStart)) {
		m_doFadeColorDown = true;
		m_velocityX = m_player1.getVelocityX();
		m_player1.setVelocityY(0.0f);
		cCameraManager::setIsLockedX(true);
		//m_player1.setIsCameraLockedX(true);
	}
	if (m_screenColor <= 0.0f) {
		std::cout << "m_player1.getVitalityMeterValue(): " << (int)m_player1.getVitalityMeterValue() << "\n";
		cSavesManager::setVitalityMeterValue(m_player1.getVitalityMeterValue());
		cSavesManager::setStaminaMeterValue(m_player1.getStaminaMeterValue());
		app->setWeatherColor(m_weatherColor);
		app->setTimerState(m_timerState);
		std::cout << m_pathLevel << " " << m_playerStart << "\n";

		sStartInfo startInfo;
		startInfo.start = m_playerStart;
		startInfo.state = m_playerState;
		startInfo.facingLeft = m_player1.getIsFacingLeft();
		startInfo.startUnlocked = m_player1.getDoStartUnlocked();
		startInfo.velocityX = m_velocityX;

		app->setState(new cInitPlayState(m_pathLevel, startInfo));
		return;
	}
}

void cPlayState::render(cApp* app) {
	if (app == nullptr) {
		return;
	}

	if (m_secondCall == false) {
		return;
	}

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

	cRenderingManager::renderPlayers(app);


	cRenderingManager::renderLevel(3, app);


	cRenderingManager::renderEntities(3, app);

	cRenderingManager::renderLevel(4, app);


	cRenderingManager::renderEntities(4, app);




	//if (!m_doHideForeground) {
	cRenderingManager::renderForegroundPlanes(app);
	//}
	cRenderingManager::renderObjects(app);
	//std::cout << "Render objects" << "\n";

	cRenderingManager::renderBitmapFonts(app);

	//cRenderingManager::renderQuadNodes(app);

	cRenderingManager::renderParticles(app);
}