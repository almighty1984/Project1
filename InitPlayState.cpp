#include "InitPlayState.h"
#include "CollisionManager.h"
#include "MusicManager.h"
#include "SavesManager.h"
#include "PlayState.h"
#include "App.h"

cInitPlayState::cInitPlayState() {
	sStartInfo startInfo;
	startInfo.start = "center";
	startInfo.state = "grass";
	init(m_pathLevel, startInfo);
	init(cSavesManager::getPathLevel(), startInfo);
}

cInitPlayState::cInitPlayState(std::string pathLevel, sStartInfo startInfo) {
	init(pathLevel, startInfo);
}

void cInitPlayState::init(std::string pathLevel, sStartInfo startInfo) {
	m_timerState = 0;
	m_playerStart = startInfo.start;
	m_playerState = startInfo.state;
	m_pathLevel = pathLevel;
	m_isFacingLeft = startInfo.facingLeft;
	m_velocityX = startInfo.velocityX;
	m_doStartUnlocked = startInfo.startUnlocked;

	for (unsigned short i = 0; i < 323; ++i) {
		keysHeld[i] = false;
	}
	m_secondCall = false;
}

cInitPlayState::~cInitPlayState() {
	std::cout << "cInitPlayState::~cInitPlayState()" << "\n";
	m_pathLevel.clear();
	m_playerStart.clear();
	m_secondCall = false;
}

void cInitPlayState::exit(cApp *app) {
	std::cout << "cInitPlayState::exit() start" << "\n";
	if (this != nullptr) {
		delete this;
	}
	std::cout << "cInitPlayState::exit() end" << "\n";
}

void cInitPlayState::enter(cApp *app, cGameState *previousState) {
	std::cout << "cInitPlayState()::enter\n";

	m_secondCall = false;
	app->setPathLevel(m_pathLevel);
	std::cout << "app->loadLevelConfig\n";
	app->clearLevelConfig();
	app->loadLevelConfig("Data\\levels.cfg");	

	std::cout << "cInitPlayState loading level ";
	if (m_levelPtr != nullptr) {
		delete m_levelPtr;
		m_levelPtr = nullptr;
	}
	std::cout << " " << m_pathLevel << " " << "\n";
	m_levelPtr = new cLevel;

	// Set levels config before loading
	m_levelPtr->setPlayerHasSprint(cSavesManager::getHasSprint());
	m_levelPtr->setPlayerHasHover(cSavesManager::getHasHover());
	m_levelPtr->setPlayerHasWhirl(cSavesManager::getHasWhirl());


	cSavesManager::clearKilled();


	m_levelPtr->load(m_pathLevel, app);

	if (cMusicManager::getDoPlay()) {		
		std::cout << app->getPathMusic(0) << "\n" << "\n" << "\n";		
		if (app->getPathMusic(0) != cMusicManager::getPath(0)) {
			std::cout << "Changing music\n";

			//sf::Time sfTime = cMusicManager::getOffset(0);
			cMusicManager::stop(0);
			cMusicManager::stop(1);

			cMusicManager::setMusic(0, app->getPathMusic(0));			
			cMusicManager::setVolume(0, app->getMusicVolume());
			//cMusicManager::setOffset(0, sfTime);
			cMusicManager::setDoLoop(0, true);
			cMusicManager::setMusic(1, app->getPathMusic(1));
			cMusicManager::setVolume(1, 0.0f);
			//cMusicManager::setOffset(1, sfTime);
			cMusicManager::setDoLoop(1, true);
		}
		/*if (cMusicManager::getDurationPrevious() != cMusicManager::getDuration(0)) {
			cMusicManager::resetOffset();
		}*/			
	}
	std::cout << "cInitPlayState()::enter finished\n";
}

void cInitPlayState::update(cApp *app, float time) {
	if (!m_secondCall) {
		m_secondCall = true;

		std::cout << "InitPlayState::update ";
		//m_levelPtr->setEntitiesLocked(true);
		//app->isGameLocked(false);
		app->setIsUpdatedEveryFrame(true);

		m_levelPtr->setIsLockedEntities(true);
	}
	
	m_levelPtr->update(app, time);

	cCollisionManager::update(app, nullptr, m_levelPtr, time);

	// Wait until rain particles have fallen a bit
	if (m_numUpdateCalls > app->getLevelStartDelay()) {
		app->setIsUpdatedEveryFrame(false);
		m_levelPtr->setIsLockedEntities(false);
		std::cout << "done." << "\n";
		std::cout << "cInitPlayState " << m_pathLevel << " " << m_playerStart << " " << m_doStartUnlocked << "\n";

		//app->sleep(1000);

		sStartInfo startInfo;
		startInfo.start = m_playerStart;
		startInfo.state = m_playerState;
		startInfo.facingLeft = m_isFacingLeft;
		startInfo.startUnlocked = m_doStartUnlocked;
		startInfo.velocityX = m_velocityX;

		app->setState(new cPlayState(m_levelPtr, m_pathLevel, startInfo));
		return;
	}
		
	m_numUpdateCalls++;
	std::cout << m_numUpdateCalls << ".";
}