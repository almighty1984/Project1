#include "PlayerMapState.h"
#include "PlayerGrassState.h"
#include "SoundsManager.h"

cPlayerMapState::cPlayerMapState()
{
	m_secondCall = false;
}

cPlayerMapState::~cPlayerMapState()
{

}

void cPlayerMapState::update(cApp *app, cPlayer *p, float time) {
	if (p == nullptr) {
		return;
	}

	if (!m_secondCall) {
		m_secondCall = true;
	}

	//// Move left
	//if(player->keysHeld[sf::Keyboard::Left]) {		
	//	std::cout << "cPlayerMapState press Left" << "\n";
	//	player->keysHeld[sf::Keyboard::Left] = false;
	//	player->setMapOffsetX(player->getMapOffsetX()-16);
	//}
	//// Move right
	//if(player->keysHeld[sf::Keyboard::Right]) {
	//	std::cout << "cPlayerMapState press Right" << "\n";
	//	player->keysHeld[sf::Keyboard::Right] = false;
	//	player->setMapOffsetX(player->getMapOffsetX()+16);		
	//}

	if (p->getIsKeyHeld(sf::Keyboard::Return)) {
		p->setIsKeyHeld(sf::Keyboard::Return, false);
		p->setState(new cPlayerGrassState);
	}
}