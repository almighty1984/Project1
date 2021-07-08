#include "GameState.h"
#include "InputManager.h"
#include "SoundsManager.h"

#include <iostream>

cGameState::cGameState() :	m_levelPtr(nullptr), 
							m_statusBarOffsetX(0.0f), m_widescreenOffset(0.0f),
							m_prevFps(0), m_numUpdateCalls(0),
							m_timerState(0.0f),							
							m_mouseX(0), m_mouseY(0),
							m_joyMovedX(0.0f), m_joyMovedY(0.0f),
							m_joyMovedCooldown(0.0f),
							m_secondCall(false),							
							m_screenColor(0.0f),
							m_weatherColor(0.0f),
							m_doChangeColorWithWeather(false), m_doDarkenWeather(false), m_doFadeColorDown(false), m_doFadeColorUp(false), m_doLightenWeather(false), m_doUseWeather(false), m_hasMouseMoved(false) {
	for (int i = 0; i < 323; ++i) {
		keysHeld[i] = false;
		joyButtonsHeld[i] = false;
		mouseButtonsHeld[i] = false;
	}
	for (char i = 0; i < 52; ++i) {
		m_alphabet[i] = 0;
	}
}

void cGameState::initWeather(cApp* app, cLevel* level) {
	std::cout << "cGameState::initWeather " << "\n";
	if (app == nullptr || level == nullptr) {
		return;
	}
	
	// Generate random weather when we just started the game
	if (app->getWeatherColor() == 0.0f) {				// No risk of rain
		if (app->getDarkenNumerator() == 0 || app->getDarkenDenominator() == 0) {
			app->setWeatherColor(255.0f);
			m_doDarkenWeather = false;
		} else if (app->getDarkenDenominator() == 1) {		// 1/1 risk, go straight to full rain
			app->setWeatherColor(175);
			m_doDarkenWeather = true;
		} else {
			for (unsigned short i = 0; i < app->getDarkenNumerator(); ++i) {
				unsigned short randNum = rand() % app->getDarkenDenominator();
				std::cout << "*randNum = " << randNum << "\n";
				if (randNum == 0/* || randNum == app->getWeatherNumerator()*/) {
					m_doDarkenWeather = true;
					app->setWeatherColor((float)(175 + rand() % 80));	// Randommize rain amount
					break;
				} else {
					m_doDarkenWeather = false;
					app->setWeatherColor(255.0f);
				}
			}
		}
	}
	m_weatherColor = app->getWeatherColor();

	if (app->getWeatherType() == 0) {
		m_doUseWeather = true;
		m_doChangeColorWithWeather = true;
	} else if (app->getWeatherType() == 1) {
		m_doUseWeather = true;
		m_doChangeColorWithWeather = false;
	} else {
		m_doUseWeather = false;
		m_doChangeColorWithWeather = false;
	}

	if (cSoundsManager::isPlaying(eSoundTag::rainOut)) {
		cSoundsManager::setVolume(eSoundTag::rainOut, 100 - (m_weatherColor / 255.0f) * 100.0f + 1);
	}
	std::cout << "cGameState::initWeather end" << "\n";
}

void cGameState::updateWeather(cApp* app, cLevel* level, float time) {
	//std::cout << "cGameState::updateWeather " << "\n";
	if (app == nullptr || level == nullptr) {
		return;
	}
	if (m_doDarkenWeather && m_weatherColor > 175.0f) {
		m_weatherColor -= time * 0.05f;
	} else if (m_doLightenWeather && m_weatherColor < 255.0f) {
		m_weatherColor += time * 0.05f;
	}

	if (m_weatherColor > 255.0f) {
		m_weatherColor = 255.0f;
	}

	if (app->getWeatherType() == 0) {
		if (cSoundsManager::isPlaying(eSoundTag::rainOut)) {
			cSoundsManager::setVolume(eSoundTag::rainOut, 100 - (m_weatherColor / 255.0f) * 100.0f + 1);
		}
	} else {
		cSoundsManager::stop(eSoundTag::rainOut);
	}
	//std::cout << "updateWeather end" << "\n";
}

void cGameState::stopWeather() {
	std::cout << "cGameState::stopWeather " << "\n";
	m_doDarkenWeather = false;
	//m_weatherColor = 255.0f;
	//app->setWeatherColor(255.0f);
	cSoundsManager::stop(eSoundTag::rainOut);
	cSoundsManager::setVolume(eSoundTag::rainOut, 0.0f);
}

bool cGameState::calculateWeather(unsigned short numerator, unsigned short denominator) {
	std::cout << "*calculateWeather " << "\n";
	std::set<int> s;
	bool b = false;
	while (s.size() < numerator) {
		int randNum = rand() % denominator;
		s.insert(randNum);
	}
	std::set<int>::iterator it = s.begin();
	while (it != s.end()) {
		std::cout << "*weather = " << (*it) << "\n";
		if ((*it) == 0) {
			b = true;
			break;
		} else {
			b = false;
		}
		++it;
	}
	std::cout << "*calculatedWeather return " << b << "\n";
	s.clear();
	return b;
}


bool cGameState::getIsPressingUp() const {
	if (keysHeld[cInputManager::getUpKey()] || (m_joyMovedY < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
		return true;
	}
	return false;
}
bool cGameState::getIsPressingDown() const {
	if (keysHeld[cInputManager::getDownKey()] || (m_joyMovedY > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
		return true;
	}
	return false;
}
bool cGameState::getIsPressingLeft() const {
	if (keysHeld[cInputManager::getLeftKey()] || (m_joyMovedX < -cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
		return true;
	}
	return false;
}
bool cGameState::getIsPressingRight() const {
	if (keysHeld[cInputManager::getRightKey()] || (m_joyMovedX > cInputManager::getJoyDeadzone() && m_joyMovedCooldown == 0.0f)) {
		return true;
	}
	return false;
}

void cGameState::setIsPressingUp(bool isPressingUp) {
	keysHeld[cInputManager::getUpKey()] = isPressingUp;
	if (!isPressingUp) {
		m_joyMovedY = 0.0f;
	} else {
		m_joyMovedY = -cInputManager::getJoyDeadzone();
	}
}
void cGameState::setIsPressingDown(bool isPressingDown) {
	keysHeld[cInputManager::getDownKey()] = isPressingDown;
	if (!isPressingDown) {
		m_joyMovedY = 0.0f;
	} else {
		m_joyMovedY = cInputManager::getJoyDeadzone();
	}
}
void cGameState::setIsPressingLeft(bool isPressingLeft) {
	keysHeld[cInputManager::getLeftKey()] = isPressingLeft;
	if (!isPressingLeft) {
		m_joyMovedX = 0.0f;
	} else {
		m_joyMovedX = -cInputManager::getJoyDeadzone();
	}
}
void cGameState::setIsPressingRight(bool isPressingRight) {
	keysHeld[cInputManager::getRightKey()] = isPressingRight;
	if (!isPressingRight) {
		m_joyMovedX = 0.0f;
	} else {
		m_joyMovedX = cInputManager::getJoyDeadzone();
	}
}