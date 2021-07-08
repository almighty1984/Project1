#include "resource.h"

#include "MusicManager.h"

#include "App.h"

#include "RenderingManager.h"
#include "InputManager.h"

//#include "JoystickManager.h"

#include "SoundBufferManager.h"
#include "SoundsManager.h"

#include "SavesManager.h"
#include "MapsManager.h"

#include "GameState.h"
#include "InitMenuState.h"
//#include "InitPlayState.h"

#include "Object.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

cApp::cApp() :
	m_secondCall(false), m_isPaused(false), m_isRunning(true), m_isLocked(false), m_isUpdatedEveryFrame(false), m_useVerticalSync(false), m_isFullscreen(false), m_isWidescreen(false), m_useEventInput(false), m_useJumpLock(false), m_useHoverLock(false), m_doHideForeground(false),
	m_windowWidth(320), m_windowHeight(240), m_frameRate(0), m_fpsCurrent(0), m_viewWidth(320), m_viewHeight(240),
	m_darkenNumerator(0), m_darkenDenominator(0), m_lightenNumerator(0), m_lightenDenominator(0),
	m_timeStep(1.0f),
	m_timerState(0.0f),
	/*m_joystickDeadzone(0.0f),*/

	m_weatherType(0),
	m_doRain(false),
	m_weatherColor(0.0f),
	m_levelStartDelay(1.0f),
	m_pathLevel(""), m_pathBackground(""), m_pathForeground(""), m_pathPlayer1("") {
	srand((int)time(0));

	m_pathTrigger = new char* [256];

	m_pathMusic[0].clear();
	m_pathMusic[1].clear();

	for (unsigned short i = 0; i < 256; ++i) {
		m_pathTrigger[i] = new char[64];
		strcpy_s(m_pathTrigger[i], 64, "Data\\Objects\\trigger_lever.cfg");
		//m_pathTrigger[i] = "Data\\Objects\\trigger_lever.cfg";
	}
}
cApp::~cApp() {
	m_pathLevel.clear();
	m_pathMusic[0].clear();
	m_pathMusic[1].clear();
	m_pathBackground.clear();
	m_pathForeground.clear();

	for (int i = 0; i < 4; ++i) {
		m_pathLeft[i].clear();
		m_pathRight[i].clear();
		m_textSign[i].clear();
		m_pathDoor[i].clear();
		m_pathBottom[i].clear();
		m_pathTop[i].clear();
	}

	m_pathPlayer1.clear();

	m_trainNumbers.clear();
	//m_platformNumbers.clear();
}

void cApp::clearTrains() {
	m_trainNumbers.clear();
	m_trainPaths.clear();
}

void cApp::init(cApp* app) {
	loadConfig("config.cfg");
	readConfigBinary();
	m_state = new cInitMenuState;
	m_state->enter(app, nullptr);
}

void cApp::writeConfigBinary() {
	std::ofstream wf("Data\\options.bin", std::ios::out | std::ios::binary);
	if (!wf) {
		std::cout << "Cannot open file!" << "\n";
		return;
	}
	sConfig config;
	config.isFullscreen = m_isFullscreen;
	config.isWidescreen = m_isWidescreen;
	config.useVerticalSync = m_useVerticalSync;
	config.windowMultiplier = m_windowMultiplier;
	config.enableMusic = cMusicManager::getDoPlay();
	config.musicVolume = m_musicVolume;
	config.useJumpLock = m_useJumpLock;
	config.useHoverLock = m_useHoverLock;

	wf.write((char*)&config, sizeof(sConfig));
	wf.close();

	return;
}

void cApp::readConfigBinary() {
	std::ifstream rf("Data\\options.bin", std::ios::out | std::ios::binary);
	if (!rf) {
		std::cout << "Cannot open file!" << "\n";
		return;
	}
	sConfig config;

	rf.read((char*)&config, sizeof(sConfig));
	rf.close();

	m_isFullscreen = config.isFullscreen;
	m_isWidescreen = config.isWidescreen;
	m_useVerticalSync = config.useVerticalSync;
	m_windowMultiplier = config.windowMultiplier;
	cMusicManager::setDoPlay(config.enableMusic);
	m_musicVolume = config.musicVolume;
	m_useJumpLock = config.useJumpLock;
	m_useHoverLock = config.useHoverLock;

	std::cout << "READ FROM BINARY" << "\n";
	std::cout << config.isFullscreen << "\n";
	std::cout << config.isWidescreen << "\n";
	std::cout << config.useVerticalSync << "\n";
	std::cout << config.windowMultiplier << "\n";
	std::cout << config.enableMusic << "\n";
	std::cout << config.musicVolume << "\n";
	std::cout << config.useJumpLock << "\n";
	std::cout << config.useHoverLock << "\n";

	if (m_isWidescreen) {
		m_viewWidth = 426;
	}
}

void cApp::shutdown() {
	m_isRunning = false;

	//cMapsManager::clearMaps();
}

void cApp::update(float time) {
	m_state->update(this, time);
}

void cApp::render() {
	m_state->render(this);
}

//Exits previous state and enters new state
void cApp::setState(cGameState* gameState) {
	cGameState* previousState = m_state;
	m_state->exit(this);
	m_state = gameState;

	std::cout << "m_state->enter(this, previousState)" << "\n";
	m_state->enter(this, previousState);
}

void cApp::sleep(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void cApp::clearPathForeground() {
	m_pathForeground.clear();
}

char* cApp::getPathTrigger(unsigned char trigger) {
	return m_pathTrigger[trigger];
}