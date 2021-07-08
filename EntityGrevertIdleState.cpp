#include "EntityGrevertDeathState.h"
#include "EntityGrevertIdleState.h"
#include "EntityGrevertAttackState.h"
#include "Player.h"
#include "SoundsManager.h"

#include "ParticleSenseGrevert.h"

cEntityGrevertIdleState::cEntityGrevertIdleState() : m_timerDelayAttack(0.0f), m_timeToDelayAttack(0) {
	m_secondCall = false;
}

cEntityGrevertIdleState::~cEntityGrevertIdleState() {

}

void cEntityGrevertIdleState::update(cApp *app, cEntity *entity, float time) {
	entity->setIsIdle(true);
	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityGrevertDeathState);
		//return;
	} else {
		entity->setAnim(eAnimTag::idle);
	}
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setIsStunned(false);
		entity->setTimerState(0.0f);
		entity->setIsDead(false);
		entity->setIsHidden(false);
		entity->setIsIdle(true);
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);


		m_timeToDelayAttack = 0 + rand() % 10;

		entity->clearSenses();
	}

	

	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	} else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}

	// Regenerate health
	if (entity->getNumHealth() > 0.0f) {
		if (entity->getNumHealth() < entity->getStartHealth()) {
			entity->setNumHealth(entity->getNumHealth() + 0.05f);
		}
		if (entity->getNumHealth() > entity->getStartHealth()) {
			entity->setNumHealth(entity->getStartHealth());
		}
	}
	
	entity->setTimerSense(entity->getTimerSense() + time);

	// Don't sense anything if entity locked
	if (entity->getIsLocked()) {
		entity->setTimerSense(0.0f);
	}

	if (entity->getTimerSense() > 5.0f && entity->getAttachedLevel() != nullptr) {
		
		entity->setTimerSense(0.0f);
		cLevel* level = entity->getAttachedLevel();
		level->addParticle(new cParticleSenseGrevert);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_grevert.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		float posX = (float)(entity->getWidth() / 2 /*+ m_particleOffsetX*/ + 4 - level->getParticleLast()->getWidth());
		level->getParticleLast()->setX(entity->getX() + posX);
		level->getParticleLast()->setLevelX(entity->getLevelX() + posX);
		level->getParticleLast()->setStartX(entity->getStartX() + posX);
		level->getParticleLast()->setVelocityX(-level->getParticleLast()->getStartVelocityX() + entity->getVelocityX());
		float posY = (float)(/*entity->getHeight() - level->getParticleLast()->getHeight() + */level->getParticleLast()->getOffsetY());
		level->getParticleLast()->setY(entity->getY() + posY);
		level->getParticleLast()->setLevelY(entity->getLevelY() + posY);
		level->getParticleLast()->setStartY(entity->getStartY() + posY);
		level->getParticleLast()->setMovedVelocityX(0.0f);
		level->getParticleLast()->setMovedVelocityY(0.0f);
		//level->getParticleLast()->update(0.0f);

		level->addParticle(new cParticleSenseGrevert);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_grevert.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		posX = (float)(entity->getWidth() / 2 /*+ m_particleOffsetX*/ - 4);
		level->getParticleLast()->setX(entity->getX() + posX);
		level->getParticleLast()->setLevelX(entity->getLevelX() + posX);
		level->getParticleLast()->setStartX(entity->getStartX() + posX);
		level->getParticleLast()->setVelocityX(level->getParticleLast()->getStartVelocityX() + entity->getVelocityX());
		posY = (float)(/*entity->getHeight() - level->getParticleLast()->getHeight() + */level->getParticleLast()->getOffsetY());
		level->getParticleLast()->setY(entity->getY() + posY);
		level->getParticleLast()->setLevelY(entity->getLevelY() + posY);
		level->getParticleLast()->setStartY(entity->getStartY() + posY);
		level->getParticleLast()->setMovedVelocityX(0.0f);
		level->getParticleLast()->setMovedVelocityY(0.0f);
		//level->getParticleLast()->update(0.0f);

		//std::cout << "EntityGrevertIdleState " << level->getParticleLast()->getX() << " " << level->getParticleLast()->getY() << "\n";
	}

	// Sensed something left
	if (!entity->getIsAttacking() && entity->getSenseCollidedLeft()) {
		if (entity->getTimerState() > 10.0f) {
			std::cout << "Sensed something left " << m_timeToDelayAttack << "\n";
			m_timerDelayAttack += time;

			if (m_timerDelayAttack > m_timeToDelayAttack) {
				if (entity->getLeftObject()->getIsDead() || entity->getLeftObject() == nullptr) {
					return;
				}
				entity->setSenseCollidedLeft(false);
				entity->setIsFacingLeft(true);
				entity->setState(new cEntityGrevertAttackState);
				return;
			}			
		}
	}
	// Sensed something right
	if (!entity->getIsAttacking() && entity->getSenseCollidedRight()) {
		if (entity->getTimerState() > 10.0f) {
			std::cout << "Sensed something right " << m_timeToDelayAttack << "\n";
			m_timerDelayAttack += time;

			entity->setMoveAcc(entity->getStartMoveAcc() / 2);
			entity->setMoveDec(entity->getStartMoveDec() / 2);
			entity->setMoveVelocity(entity->getStartMoveVelocity() / 2);

			if (m_timerDelayAttack > m_timeToDelayAttack) {
				if (entity->getRightObject()->getIsDead() || entity->getRightObject() == nullptr) {
					return;
				}			

				entity->setSenseCollidedRight(false);
				entity->setIsFacingLeft(false);
				entity->setState(new cEntityGrevertAttackState);
				return;
			}
		}
	}
	

	if (entity->getTimeBeingIdle() > 20 + rand() % 20) {
		//std::cout << "EntityGrevertIdleState " << entity->getTimeBeingIdle() << "\n";
		entity->setTimeBeingIdle(0.0f);
		if (rand() % 2 == 0) {
			entity->setIsFacingLeft(true);
		} else {
			entity->setIsFacingLeft(false);
		}
	}

	if (entity->getIsFacingLeft()) {
		if (entity->getVelocityX() > -entity->getMoveVelocity()) {
			entity->setVelocityX(entity->getVelocityX() - entity->getMoveAcc());
		}
	} else {
		if (entity->getVelocityX() < entity->getMoveVelocity()) {
			entity->setVelocityX(entity->getVelocityX() + entity->getMoveAcc());
		}
	}

	entity->setTimeBeingIdle(entity->getTimeBeingIdle() + time);
	entity->setTimerState(entity->getTimerState() + time);
	
}