#include "CameraManager.h"
#include "Particle.h"

bool cCameraManager::m_secondCall = false;
bool cCameraManager::m_isLockedX = false;
bool cCameraManager::m_isLockedY = false;
float cCameraManager::m_offsetX = 0.0f;
float cCameraManager::m_offsetY = 0.0f;
float cCameraManager::m_scrollLimitUp = -48.0f;
float cCameraManager::m_scrollLimitDown = 32.0f;
float cCameraManager::m_x = 0.0f;
float cCameraManager::m_y = 0.0f;
float cCameraManager::m_velocityX = 0.0f;
float cCameraManager::m_velocityY = 0.0f;

void cCameraManager::scrollY(cLevel* level, cPlayer* player1, float scrollY) {
	if (!player1->getIsOnGround()) {
		return;
	}
	if (m_offsetY + scrollY < m_scrollLimitUp) {
		return;
		//m_offsetY = m_scrollLimitUp;
	} else if (m_offsetY + scrollY > m_scrollLimitDown) {
		return;
		//m_offsetY = m_scrollLimitDown;
	}

	if (player1->getIsPressingUp() && scrollY > 0.0f || player1->getIsPressingDown() && scrollY < 0.0f) {
		return;
	}

	//if (m_offsetY > m_scrollLimitUp && m_offsetY < m_scrollLimitDown) {
	level->scrollY(scrollY);
	player1->setY(player1->getY() - scrollY);
	m_offsetY += scrollY;
	//}
}

void cCameraManager::resetY(cLevel* level, cPlayer* player1, float scrollY) {
	if (!player1->getIsOnGround() || player1->getIsPressingUp() || player1->getIsPressingDown()) {
		return;
	}
	if (m_offsetY == 0.0f) {
		return;
	}
	if (m_offsetY > 0.0f) {
		scrollY = -abs(scrollY);
	}
	if (m_offsetY < 0.0f) {
		scrollY = abs(scrollY);
	}

	level->scrollY(scrollY);
	player1->setY(player1->getY() - scrollY);
	m_offsetY += scrollY;

}

void cCameraManager::update(cApp *app, cLevel* level, cPlayer *player1, float time) {
	if (level == nullptr || player1 == nullptr) {
		return;
	}
	if (!m_secondCall) {
		m_secondCall = true;
		level->update(app, time);
		//level->scrollY(-1.0f);
	}
	//std::cout << level->getX() << "\n";

	

	if (player1->getIsDead()) {
		m_isLockedX = true;
		m_isLockedY = true;
	}

	//std::cout << m_offsetY << "\n";

	// Scroll up and down
	if (!player1->getIsPressingLeft() && !player1->getIsPressingRight()) {		
		if ((player1->getTimePressingUp() > 20.0f/* && m_offsetY > m_scrollLimitUp*/) || (player1->getTimePressingDown() > 20.0f /*&& m_offsetY < m_scrollLimitDown*/)) {
			
			if (player1->getIsPressingUp()) {
				scrollY(level, player1, -1.0f);
			} else if (player1->getIsPressingDown()) {
				scrollY(level, player1, 1.0f);
			}		
		}
	}

	
	
	float a = 0.0f;
	app->getIsWidescreen() ? a = 56.0f + m_offsetX : a = m_offsetX;
	if (level->getX() > 0.0f+a) {
		if ((player1->getMiddleX() < 160 - 1.0f + m_offsetX) && !m_isLockedX) {
			level->scrollX((player1->getX() - player1->getPreviousX()));
			player1->setX(160 - player1->getWidth() / 2 - 1.0f + m_offsetX);
		}
	}/* else {			
		cRenderingManager::setIsViewLocked(true);
	}*/

	app->getIsWidescreen() ? a = 64.0f + m_offsetX : a = m_offsetX;
	
	if (level->getX()+a < level->getNumColumns() * 16 - 320 + 4) {
		if (player1->getMiddleX() > 160 + 1.0f + m_offsetX &&	!m_isLockedX) {
			level->scrollX((player1->getX() - player1->getPreviousX()));
			player1->setX(160 - player1->getWidth() / 2 + 1.0f + m_offsetX);
		}
	}

	if (level->getY() > 0.0f) {
		if (player1->getY() < 120.0f - player1->getHeight() * 0.5f - 48.0f - m_offsetY && !m_isLockedY) {
			level->scrollY( (player1->getY() - player1->getPreviousY()) );
			player1->setY(120.0f - player1->getHeight() * 0.5f - 48.0f - m_offsetY);
		}
	}
	if (level->getY() < ((level->getNumRows()*16-2) - app->getViewHeight()) ) {
		if (player1->getY() > 120.0f - player1->getHeight() * 0.5f - m_offsetY && !m_isLockedY) {
			level->scrollY( (player1->getY()-player1->getPreviousY()) );
			player1->setY(120.0f - player1->getHeight() * 0.5f - m_offsetY);
		}
	}
}