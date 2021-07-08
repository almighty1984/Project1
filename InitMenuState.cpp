#include "InitMenuState.h"
//#include "TextureManager.h"
#include "MenuState.h"

#include "App.h"

#include "MusicManager.h"

//#include <iostream>

cInitMenuState::cInitMenuState() {
	std::cout << "cInitMenuState::cInitMenuState()" << "\n";
	for (int i=0; i<323; ++i) {
		keysHeld[i] = false;
	}
	m_secondCall = false;
	//cTextureManager::unloadAll();
}


cInitMenuState::~cInitMenuState() {
	std::cout << "cInitMenuState::~cInitMenuState()" << "\n";
	m_secondCall = false;
}

void cInitMenuState::exit(cApp *app) {
	std::cout << "cInitMenuState::exit() start" << "\n";
	if (this != nullptr) {
		delete this;
	}
	std::cout << "cInitMenuState::exit() end" << "\n";
}
void cInitMenuState::enter(cApp *app, cGameState *previousState) {
	//Create the stuff we need, might be able to scrap this state entirely and go directly to menustate
	//and maybe have the initializing between the menustate and the state that handles running the game

	std::cout << "cInitMenuState::enter(cApp *app, cGameState *previousState) {" << "\n";
	app->setPathLevel("Data\\Levels\\5000_5000.bin");
	app->clearTrains();
	app->loadLevelConfig("Data\\levels.cfg");

	m_levelPtr = new cLevel;
	m_levelPtr->load("Data\\Levels\\5000_5000.bin", app);

	if (cMusicManager::getDoPlay()) {
		std::cout << app->getPathMusic(0) << "\n" << "\n" << "\n";
		if (app->getPathMusic(0) != cMusicManager::getPath(0)) {
			std::cout << "Changing music" << "\n";
			cMusicManager::setDoLoop(0, true);
			cMusicManager::setMusic(0, app->getPathMusic(0));
			cMusicManager::setVolume(0, app->getMusicVolume());
			cMusicManager::play(0);
		}
	}

	
	//delete this;
	//std::cout << "new cMenuState done" << "\n";
}

//
void cInitMenuState::update(cApp *app, float time) {
	if (m_secondCall == false) {
		m_secondCall = true;
		//app->sleep(200);
		app->setState(new cMenuState(m_levelPtr));
	}
}

//void cInitMenuState::render(const cApp *app) const
//{	
//
//}
