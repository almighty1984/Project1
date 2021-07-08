#include "PlayerLedgeState.h"
#include "PlayerGrassState.h"
#include "SoundsManager.h"


cPlayerLedgeState::cPlayerLedgeState() : m_ledge(nullptr), m_doChangeState(false), m_timerClimb(0.0f), m_timerSideStep(0.0f) {
	m_secondCall = false;
}

cPlayerLedgeState::~cPlayerLedgeState()
{

}

void cPlayerLedgeState::update(cApp* app, cPlayer* p, float time) {
	if (app == nullptr || p == nullptr) {
		return;
	}

	

	if (!m_secondCall) {
		m_secondCall = true;
		p->setIsOnLedge(true);
		p->setLockJump(true);
		p->setIsPressingJump(false);
		//p->setDoSpawnSenses(false);
		cSoundsManager::stop(eSoundTag::wallSlide);
		cSoundsManager::stop(eSoundTag::hover);
		cSoundsManager::play(eSoundTag::block);

		p->setAnim(eAnimTag::ledge);
		p->setTileOffsetX(0.0f);
		m_ledge = nullptr;
		if (p->getIsNearWallLeft() && p->getLeftObject() != nullptr) {
			m_ledge = p->getLeftObject();			
			p->setX(m_ledge->getRight() - p->getSubtractLeft());			
			p->setStartX(m_ledge->getStartX() - p->getSubtractLeft());
			p->setLevelX(m_ledge->getLevelX() - p->getSubtractLeft());
			
		} else if (p->getIsNearWallRight() && p->getRightObject() != nullptr) {
			m_ledge = p->getRightObject();
			p->setX(m_ledge->getLeft() + p->getSubtractRight());
			p->setStartX(m_ledge->getStartX() + p->getSubtractRight());

			p->setLevelX(m_ledge->getLevelX() + p->getSubtractRight());
		}
		
		p->setY(m_ledge->getTop() - p->getSubtractUp() - 8);
		p->setStartY(m_ledge->getStartY() - p->getSubtractUp() - 8);

		p->setLevelY(m_ledge->getLevelY() - p->getSubtractUp() - 8);
	}

	if (m_ledge == nullptr) {
		m_doChangeState = true;
	}

	if (m_doChangeState) {
		std::cout << "changed state\n";
		p->setDelayCollisionLevel(1.0f);
		p->setIsNearWallLeft(false);
		p->setIsNearWallRight(false);
		//p->setIsOnGround(true);

		p->setDoSpawnSenses(true);

		p->setNumJumps(0);
		/*p->setVelocityY(0.0f);
		p->setY(m_ledge->getY() - p->getHeight() + p->getSubtractDown());
		p->setStartY(m_ledge->getStartY() - p->getHeight() + p->getSubtractDown());
		p->setLevelY(m_ledge->getLevelY() - p->getHeight() + p->getSubtractDown());*/
		p->clearSenses();
		m_doChangeState = false;
		//p->setIsPressingUp(false);
		p->setState(new cPlayerGrassState);
		return;
	}

	
	

	if (m_timerClimb == 0.0f && m_timerSideStep == 0.0f) {
		

		p->setVelocityX(0.0f);
		p->setVelocityY(0.0f);
	}
	
	

	if (p->getIsPressingJump() && (p->getIsNearWallLeft() && p->getIsPressingRight() || p->getIsNearWallRight() && p->getIsPressingLeft()) && p->getAnimTag() == eAnimTag::ledge) {
		// Wall jump right
		if (p->getIsNearWallLeft() && !p->getIsPressingLeft()) {
			p->setIsPressingJump(false);
			p->setHasJumped(true);

			p->setLockJump(true);
			p->setLockHover(true);

			p->setIsPressingWallJump(true);
			p->setIsFacingLeft(false);
			m_doChangeState = true;
			return;
		}
		// Wall jump left
		if (p->getIsNearWallRight() && !p->getIsPressingRight()) {
			p->setIsPressingJump(false);
			p->setHasJumped(true);

			p->setLockJump(true);
			p->setLockHover(true);

			p->setIsPressingWallJump(true);
			p->setIsFacingLeft(true);
			m_doChangeState = true;
			return;
		}
	}
	if (m_timerClimb == 0.0f && p->getIsPressingUp() || (p->getIsPressingJump() && (p->getIsNearWallRight() && p->getIsPressingRight() || p->getIsNearWallLeft() && p->getIsPressingLeft())) ) {
		if (!cSoundsManager::isPlaying(eSoundTag::swingDetach)) {
			cSoundsManager::play(eSoundTag::swingDetach);
		}
		m_timerClimb += time;
	}
	if (p->getIsPressingDown() || p->getTop() > m_ledge->getMiddleY()) {
		p->setIsPressingDown(false);
		p->setDownThrustCooldownValue(10.0f);

		p->setIsFacingLeft(!p->getIsFacingLeft());

		p->getIsFacingLeft() ? p->setVelocityX(-0.5f) : p->setVelocityX(0.5f);

		m_doChangeState = true;
	}

	if (m_timerClimb > 0.0f && !m_doChangeState) {
		m_timerClimb += time;

		if (p->getAnimTag() != eAnimTag::climb) {
			p->setTileOffsetX(0.0f);
		}
		p->setAnim(eAnimTag::climb);

		p->setVelocityY(p->getVelocityY() - 0.1f);

		


		if (m_timerSideStep == 0.0f && (p->getBottom()-2 < m_ledge->getTop() || p->getTop() > m_ledge->getBottom())) {
			std::cout << "Got above left object" << "\n";
			m_timerSideStep += time;
			m_timerClimb = 0.0f;
			p->setVelocityY(p->getVelocityY() * 0.5f);
		}


		
	}

	if (m_timerSideStep > 0.0f) {
		m_timerSideStep += time;
		//p->setVelocityY(0.0f);
		
		float velX = 0.2f;
		if (p->getIsFacingLeft()) {
			velX = -velX;
			if (p->getMiddleX() < m_ledge->getRight()) {
				m_doChangeState = true;
			}
		}
		if (!p->getIsFacingLeft()) {
			if (p->getMiddleX() > m_ledge->getLeft()) {
				m_doChangeState = true;
			}
		}
		p->setMovedVelocityX(p->getMovedVelocityX() + velX);

		if (m_timerSideStep > 100.0f) {
			m_doChangeState = true;
		}
	}

	
	
}