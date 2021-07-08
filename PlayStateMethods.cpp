#include "PlayState.h"
#include "SoundsManager.h"
#include "InputManager.h"

bool cPlayState::checkChangeLevel(cApp* app, cPlayer& player, std::string& newPathLevel, std::string& newPlayerStart) {
	if (app == nullptr || &player == nullptr/* || player.getIsDead() || !m_secondCall*/) {
		return false;
	}
	float boundsLeft = -64.0f;
	float boundsRight = 272.0f;

	if (app->getIsWidescreen()) {
		boundsLeft = -100.0f;
		boundsRight = 330.0f;
	}
	if (player.getX() < boundsLeft || player.getX() > boundsRight) {
		if (player.getNextLevel().substr(0, 10) == "level_left") {
			newPlayerStart = "right" + m_player1.getNextLevel().substr(11, 1);
			int num = atoi(m_player1.getNextLevel().substr(11, 1).c_str());
			newPathLevel = app->getPathLeft(num);
			return true;
		} else if (player.getNextLevel().substr(0, 11) == "level_right") {
			newPlayerStart = "left" + m_player1.getNextLevel().substr(12, 1);
			int num = atoi(m_player1.getNextLevel().substr(12, 1).c_str());
			newPathLevel = app->getPathRight(num);
			return true;
		}	
	} else if (player.getY() > app->getViewHeight() - player.getHeight() / 2) {
		if (player.getNextLevel().substr(0, 13) == "level_bottom_") {
			newPlayerStart = "bottom" + player.getNextLevel().substr(13, 1);
			int num = atoi(newPlayerStart.substr(6, 1).c_str());
			newPathLevel = app->getPathBottom(num);
			return true;
		}		
	} else if (player.getY() < -64.0f && !player.getIsDead() && m_secondCall) {
		if (player.getNextLevel().substr(0, 10) == "level_top_") {
			newPlayerStart = "top" + player.getNextLevel().substr(10, 1);
			int num = atoi(newPlayerStart.substr(3, 1).c_str());
			newPathLevel = app->getPathTop(num);
			return true;
		}
	} else if (player.getIsNearDoor() && player.getIsPressingUp() && !cSoundsManager::isPlaying(eSoundTag::chestOpen)) {
		//player.setIsPressingUp(false);
		for (unsigned char i = 0; i < 4; ++i) {
			if (player.getIsInDoor(i)/* && !app->getPathDoor(i).empty() && app->getPathDoor(i).size() > 17*/) {
				cSoundsManager::stop(eSoundTag::chestOpen);
				cSoundsManager::play(eSoundTag::chestOpen);
				newPathLevel = app->getPathDoor(i);
				
				std::stringstream ss;
				ss << (int)i;
				newPlayerStart = "door" + ss.str();
				//std::cout << newPathLevel << " " << newPlayerStart << "\n";
				return true;
			}
		}
	}
	return false;
}

void cPlayState::initPlayerStart(cApp* app) {
	if (app == nullptr || m_levelPtr == nullptr || m_playerStart.size() < 4) {
		return;
	}

	cCameraManager::setIsLockedX(false);
	cCameraManager::setIsLockedY(false);
	
	std::cout << "m_playerStart: " << m_playerStart << "\n";
	m_player1.setIsOnGround(true);
	/*m_levelPtr->setPlanePositionX(256.0f);
	m_levelPtr->setPlanePositionY(256.0f);*/

	if (m_playerStart.substr(0, 4) == "left") {
		m_player1.setStartX(0);
		m_player1.setVelocityX(0.0f);
		m_player1.setVelocityY(0.0f);

		unsigned short i = 0;
		std::stringstream tmpStrStr;
		tmpStrStr << m_playerStart.substr(4, 1);
		tmpStrStr >> i;

		m_player1.setStartY(m_levelPtr->getPlayerStart("left", i, 'y') + 16 - m_player1.getHeight());

		if (m_doStartUnlocked) {
			cCameraManager::setIsLockedX(true);
			//m_player1.setIsCameraLockedX(false);
			m_levelPtr->scrollX(m_levelPtr->getPlayerStart("left", i, 'x') - 160);
			m_player1.setX((float)(160 - m_player1.getWidth() / 2));
		} else {
			cCameraManager::setIsLockedX(true);
			//m_player1.setIsCameraLockedX(true);
			float offsetX = 0.0f;
			app->getIsWidescreen() ? offsetX = 48.0f : offsetX = 0.0f;

			m_levelPtr->scrollX(m_levelPtr->getPlayerStart("left", i, 'x') - 16.0f + offsetX);
			m_player1.setX(-offsetX -(m_player1.getWidth() * 0.25f));
		}
		if (m_levelPtr->getPlayerStart("left", i, 'y') - 120 <= 0.0f) {
			m_levelPtr->scrollY(24);
			std::cout << "left start Y  <= 0.0f" << "\n";
			m_player1.setY((app->getViewHeight() / 2) + (m_levelPtr->getPlayerStart("left", i, 'y')+2 - app->getViewHeight() / 2 - m_player1.getHeight()));
			//m_player1.setLevelY((app->getViewHeight() / 2 - 32) + (m_levelPtr->getPlayerStart("left", i, 'y') - app->getViewHeight() / 2 - 16));
		} else if ((m_levelPtr->getPlayerStart("left", i, 'y')) >= m_levelPtr->getNumRows()*16-app->getViewHeight()/2) {
			std::cout << "left start Y  >= m_levelPtr->getNumRows()*16-app->getViewHeight()/2" << "\n";
			m_levelPtr->scrollY((float)(m_levelPtr->getNumRows()*16-app->getViewHeight()-0));
			//m_player1.setY(120-48);
			m_player1.setY(app->getViewHeight() - (m_levelPtr->getNumRows()*16-m_levelPtr->getPlayerStart("left", i, 'y')) - m_player1.getHeight());
		} else {
			std::cout << "left start Y  NOT <= 0.0f OR >= m_levelPtr->getNumRows()*16-app->getViewHeight()/2" << "\n";
			m_levelPtr->scrollY(m_levelPtr->getPlayerStart("left", i, 'y') - app->getViewHeight() / 2 /*<--might need to fix*/ );
			m_player1.setY((float)(app->getViewHeight()/2)-64);
		}
		//m_player1.setLevelX( m_levelPtr->getPlayerStart("left",i,'x') );
		//m_player1.setLevelY( m_levelPtr->getPlayerStart("left",i,'y') + 0);
		
		m_player1.setIsFacingLeft(false);			
		m_player1.setInLevelChangeArea(true);				
		cRenderingManager::setIsViewLocked(true);		
		
		//if (m_doStartUnlocked) {			
		//	m_player1.setX(160 - m_player1.getWidth() / 2));
		//	//m_player1.setY(0.0f);
		//}
	} else if (m_playerStart.substr(0, 5) == "right") {
		m_player1.setStartX((float)(m_levelPtr->getNumColumns()*16 - m_player1.getWidth()));
		m_player1.setVelocityX(0.0f);
		m_player1.setVelocityY(0.0f);

		unsigned short i=0;
		std::stringstream tmpStrStr;
		tmpStrStr << m_playerStart.substr(5,1);
		tmpStrStr >> i;

		m_player1.setStartY(m_levelPtr->getPlayerStart("right", i, 'y')+16-64);

		if (m_doStartUnlocked) {
			cCameraManager::setIsLockedX(false);
			//m_player1.setIsCameraLockedX(false);
			m_levelPtr->scrollX(m_levelPtr->getPlayerStart("right", i, 'x') - 160 - 0);
			m_player1.setX((float)(160 - m_player1.getWidth() / 2));
		} else {
			cCameraManager::setIsLockedX(true);
			//m_player1.setIsCameraLockedX(true);

			float offsetX = 0.0f;
			app->getIsWidescreen() ? offsetX = 378.0f : offsetX = 320.0f;

			m_levelPtr->scrollX(m_levelPtr->getPlayerStart("right", i, 'x') - offsetX);
			m_player1.setX(offsetX - (m_player1.getWidth() * 0.75f));
		}
		if ((m_levelPtr->getPlayerStart("right", i, 'y') + 16 - m_player1.getHeight()) <= app->getViewHeight() / 2 - 0) {
			// Over the top
			m_player1.setY((app->getViewHeight() / 2) + (m_levelPtr->getPlayerStart("right", i, 'y') + 16 - m_player1.getHeight() - app->getViewHeight() / 2 - 0));
		} 
		else if (m_levelPtr->getPlayerStart("right", i, 'y') - m_player1.getHeight() >= m_levelPtr->getNumRows()*16-app->getViewHeight()/2 ) {
			// Below the bottom
			m_levelPtr->scrollY((float)(m_levelPtr->getNumRows()*16-app->getViewHeight()-16));
			//m_player1.setY(120-48);
			m_player1.setY(app->getViewHeight()-(m_levelPtr->getNumRows()*16-m_levelPtr->getPlayerStart("right", i, 'y') - m_player1.getHeight())-64);
		} else {
			// In the middle
			m_levelPtr->scrollY(m_levelPtr->getPlayerStart("right", i, 'y') - m_player1.getHeight() - app->getViewHeight() / 2 + 48);
			m_player1.setY(120-48);
		}
		//m_player1.setLevelX(m_levelPtr->getPlayerStart("right", i, 'x') );
		//m_player1.setLevelY(m_levelPtr->getPlayerStart("right", i, 'y') + 0);
				
		cCameraManager::setIsLockedY(false);
		//m_player1.setIsCameraLockedY(false);	
		m_player1.setIsFacingLeft(true);
		m_player1.setInLevelChangeArea(true);
		cRenderingManager::setIsViewLocked(true);

		//if (m_doStartUnlocked) {
		//	m_player1.setIsCameraLockedX(false);		
		//	m_player1.setX((float)(160 - m_player1.getWidth() / 2));
		//	//m_player1.setY(0.0f);
		//}
	} else if (m_playerStart.substr(0, 4) == "door") {
		//cRenderingManager::setIsViewLocked(false);
		unsigned short i = 0;
		std::stringstream tmpStrStr;
		tmpStrStr << m_playerStart.substr(4, 1);
		tmpStrStr >> i;

		m_player1.setStartX(m_levelPtr->getPlayerStart("door", i, 'x'));
		m_player1.setStartY(m_levelPtr->getPlayerStart("door", i, 'y')+16-64);

		if (app->getIsWidescreen()) {
			/*m_levelPtr->scrollX(m_levelPtr->getPlayerStart("door", i, 'x'));
			m_player1.setX(320 / 2 - 56);*/
			if (m_levelPtr->getPlayerStart("door", i, 'x')-(20*16/2) >= m_levelPtr->getNumColumns()*16-368) {
				m_levelPtr->scrollX((float)(m_levelPtr->getNumColumns()*16-368));
				m_player1.setX(m_levelPtr->getPlayerStart("door", i, 'x') - (20*16/2) - m_levelPtr->getX() + m_player1.getWidth() / 2 + 16 + 16);
				cCameraManager::setIsLockedX(true);
				//m_player1.setIsCameraLockedX(true);
			} else if (m_levelPtr->getPlayerStart("door", i, 'x') - (20*16/2) <= 0.0f) {
				m_levelPtr->scrollX(64);
				cCameraManager::setIsLockedX(true);
				//m_player1.setIsCameraLockedX(true);
				m_player1.setX(m_levelPtr->getPlayerStart("door", i, 'x') - m_player1.getWidth() / 2 - 0);
			} else {
				m_levelPtr->scrollX(m_levelPtr->getPlayerStart("door", i, 'x') - 20*16/2-0);
				m_player1.setX((float)(160 - m_player1.getWidth() / 2));
			}	
		} else {
			if ((m_levelPtr->getPlayerStart("door", i, 'x')-20*16/2) - m_player1.getHeight() >= m_levelPtr->getNumColumns()*16 - app->getViewWidth()) {
				m_levelPtr->scrollX((float)(m_levelPtr->getNumColumns()*16 - app->getViewWidth()));
				m_player1.setX(m_levelPtr->getPlayerStart("door", i, 'x') - (20*16/2) - m_levelPtr->getX() + m_player1.getWidth() / 2 + 16 + 16);
				cCameraManager::setIsLockedX(true);
				//m_player1.setIsCameraLockedX(true);
			} else if (m_levelPtr->getPlayerStart("door", i, 'x') - m_player1.getHeight() -(20*16/2) <= 0.0f) {
				//m_levelPtr->scrollX(0.0f);
				cCameraManager::setIsLockedX(true);
				//m_player1.setIsCameraLockedX(true);
				m_player1.setX(m_levelPtr->getPlayerStart("door", i, 'x') -m_player1.getWidth() / 2);
			} else {
				m_levelPtr->scrollX(m_levelPtr->getPlayerStart("door", i, 'x') -20*16/2-0);
				m_player1.setX((float)(160 - m_player1.getWidth() / 2));
			}
		}
		if ((m_levelPtr->getPlayerStart("door", i, 'y') - m_player1.getHeight() - app->getViewHeight() / 2 - 0) <= 0.0f) {
			m_player1.setY((app->getViewHeight() / 2) + (m_levelPtr->getPlayerStart("door", i, 'y') - m_player1.getHeight() - app->getViewHeight() / 2 - 0));
			//m_player1.setLevelY((app->getViewHeight() / 2 - 32) + (m_levelPtr->getPlayerStart("left", i, 'y') - app->getViewHeight() / 2 - 16));
		} else if (m_levelPtr->getPlayerStart("door", i, 'y') - m_player1.getHeight() >= m_levelPtr->getNumRows() * 16 - app->getViewHeight() / 2) {
			m_levelPtr->scrollY((float)(m_levelPtr->getNumRows() * 16 - app->getViewHeight() - 16));
			//m_player1.setY(120-48);
			m_player1.setY(app->getViewHeight() - m_levelPtr->getNumRows() * 16 - m_levelPtr->getPlayerStart("door", i, 'y') - m_player1.getWidth() / 2);
		} else {
			m_levelPtr->scrollY(m_levelPtr->getPlayerStart("door", i, 'y') - m_player1.getHeight() - app->getViewHeight() / 2 + 48 /*<--might need to fix*/);
			m_player1.setY(120-48);
		}		
		//m_player1.setLevelX(m_levelPtr->getPlayerStartDoor0X());
		//m_player1.setLevelY(m_levelPtr->getPlayerStartDoor0Y());
		m_player1.setIsInDoor(i, true);
	} else if (m_playerStart.substr(0,6) == "bottom") {
		unsigned short i = 0;
		std::stringstream tmpStrStr;
		tmpStrStr << m_playerStart.substr(6, 1);
		tmpStrStr >> i;		
		if (m_levelPtr->getPlayerStart("top", i, 'x') <= 192.0f) {
			//cCameraManager::setIsLockedX(true);
			//m_player1.setIsCameraLockedX(true);
			if (app->getIsWidescreen()) {
				m_levelPtr->scrollX( m_levelPtr->getPlayerStart("left",0,'x')+3*16 );
				m_player1.setX((float)(m_levelPtr->getPlayerStart("top", i, 'x') - m_player1.getWidth() + 16));
				//m_player1.setY(128.0f);
			} else {
				m_levelPtr->scrollX( m_levelPtr->getPlayerStart("left",0,'x') );				
				m_player1.setX((float)(m_levelPtr->getPlayerStart("top", i, 'x') - m_player1.getWidth() / 2));
			}			
		} else {
			m_levelPtr->scrollX( m_levelPtr->getPlayerStart("top", i, 'x') - (20*16)/2 );
			m_player1.setX((float)(160 - m_player1.getWidth() / 2));
		}

		m_player1.setStartX(m_levelPtr->getPlayerStart("top", i, 'x') + 8 - m_player1.getWidth() / 2);
		m_player1.setStartY(m_levelPtr->getPlayerStart("top", i, 'y') + 16 - m_player1.getHeight());
		m_player1.setLevelX( m_levelPtr->getPlayerStart("top", i, 'x') + 8 - m_player1.getWidth() / 2);
		m_player1.setLevelY( m_levelPtr->getPlayerStart("top", i, 'y'));
		m_player1.setY(-48.0f);
		m_player1.setVelocityX(0.0f);
		//m_player1.setVelocityY(m_player1.getFallVelocity());		
	} else if (m_playerStart.substr(0, 3) == "top") {
		unsigned short i = 0;
		std::stringstream tmpStrStr;
		tmpStrStr << m_playerStart.substr(3, 1);
		tmpStrStr >> i;
				
		if (m_levelPtr->getPlayerStart("bottom", i, 'x') <= 192.0f) {
			//cCameraManager::setIsLockedX(true);
			//m_player1.setIsCameraLockedX(true);
			if (app->getIsWidescreen()) {
				m_levelPtr->scrollX(m_levelPtr->getPlayerStart("left", 0, 'x') + 3 * 16);
				m_player1.setX((float)(m_levelPtr->getPlayerStart("bottom", i, 'x') - m_player1.getWidth() + 16));
				//m_player1.setY(128.0f);
			} else {
				m_levelPtr->scrollX(m_levelPtr->getPlayerStart("left", 0, 'x'));
				m_player1.setX((float)(m_levelPtr->getPlayerStart("bottom", i, 'x') - m_player1.getWidth() / 2));
			}
		} else {
			m_levelPtr->scrollX(m_levelPtr->getPlayerStart("bottom", i, 'x') - (20 * 16) / 2);
			m_player1.setX((float)(160 - m_player1.getWidth() / 2));
		}
		m_levelPtr->scrollY((float)(m_levelPtr->getNumRows() * 16 - 15 * 16));
		m_player1.setLevelX(m_levelPtr->getPlayerStart("bottom", i, 'x') + 8 - m_player1.getWidth() / 2);
		m_player1.setLevelY(m_levelPtr->getPlayerStart("bottom", i, 'y'));
		m_player1.setStartX(m_levelPtr->getPlayerStart("bottom", i, 'x') + 8 - m_player1.getWidth() / 2);
		m_player1.setStartY(m_levelPtr->getPlayerStart("bottom", i, 'y') );
		m_player1.setY(240.0f-32.0f);
		m_player1.setVelocityY(-6.0f);
	} else {

		float startX = m_levelPtr->getPlayerStart("center", 0, 'x');

		std::cout << "startX: " << startX << "\n";
		std::cout << m_levelPtr->getNumColumns() * 16 << "\n";

		float offsetX = 0.0f;

		if (app->getIsWidescreen()) {
			if (startX < 216) {
				offsetX = 216 - startX;
			} else if (startX > m_levelPtr->getNumColumns() * 16  - (13*16)) {
				offsetX = -(m_levelPtr->getNumColumns() * 16 - startX);
			}
		} else if (!app->getIsWidescreen()) {
			if (startX < 160) {
				offsetX = 160 - startX;
			} else if (startX > m_levelPtr->getNumColumns() * 16 - 168) {
				offsetX = -168;
			}
		}

		m_player1.setStartX(m_levelPtr->getPlayerStart("center", 0, 'x') + 8 - m_player1.getWidth() / 2);
		m_player1.setStartY(m_levelPtr->getPlayerStart("center", 0, 'y') + 16 - m_player1.getHeight());
		m_player1.setLevelY(m_levelPtr->getPlayerStart("center", 0, 'x') + 8 - m_player1.getWidth() / 2);
		m_player1.setLevelY(m_levelPtr->getPlayerStart("center", 0, 'y') + 16 - m_player1.getHeight());
		m_levelPtr->getStartObject()->setIsDead(true);
		
		
		m_levelPtr->scrollX( m_levelPtr->getPlayerStart("center", 0, 'x') - 160 + offsetX);


		m_player1.setX(160 - m_player1.getWidth() / 2 - offsetX);

		if ((int)(m_levelPtr->getPlayerStart("center", 0, 'y') + 16) <= app->getViewHeight() / 2) {
			// Over the top
			//cCameraManager::setIsLockedY(true);
			m_player1.setY(120 + m_levelPtr->getPlayerStart("center", 0, 'y') + 16 - 120 - m_player1.getHeight());
		} else if (m_levelPtr->getPlayerStart("center", 0, 'y') >= m_levelPtr->getNumRows() * 16 - 120) {
			// Below the bottom
			m_levelPtr->scrollY((float)(m_levelPtr->getNumRows() * 16 - app->getViewHeight() - 0));
			m_player1.setY(app->getViewHeight() - (m_levelPtr->getNumRows() * 16 - m_levelPtr->getPlayerStart("center", 0, 'y')) + 16 - m_player1.getHeight());
		} else {
			// In between
			m_levelPtr->scrollY(m_levelPtr->getPlayerStart("center", 0, 'y') - 120 + cCameraManager::getOffsetY()/*<--might need to fix*/);
			m_player1.setY(120.0f + 16.0f - m_player1.getHeight() - cCameraManager::getOffsetY());
		}
	}
}