#include "EntityFlylingFlightState.h"
#include "EntityFlylingChargeState.h"
#include "EntityFlylingDeathState.h"
#include "Player.h"
#include "SoundsManager.h"
#include "ParticleSense.h"

//#include <math.h>

cEntityFlylingFlightState::cEntityFlylingFlightState() {
	m_secondCall = false;
}

cEntityFlylingFlightState::~cEntityFlylingFlightState() {

}

void cEntityFlylingFlightState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setVelocityY(0.0f);
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setIsHurting(false);
	}

	if (!entity->getIsFacingLeft()) {
		entity->setVelocityX(0.75f);
	} else {
		entity->setVelocityX(-0.75f);
	}

	entity->setVelocityY( sin(entity->getLevelX() * 0.125f ) );
	
	// Death animation
	if (entity->getIsDead()) {	
		//m_velocityX = 0.0f;
		entity->setTimeBeingDead( entity->getTimeBeingDead() + time );
		entity->setAnim(eAnimTag::death);
	} else {
		entity->setAnim(eAnimTag::walk);
	}
	
	// Don't sense anything if entity locked
	if (entity->getIsLocked()) {
		entity->setTimerSense(0.0f);
	}
	entity->setTimerSense(entity->getTimerSense() + time);
	if (entity->getTimerSense() > 5.0f) {
		entity->setTimerSense(0.0f);
		cLevel *level = entity->getAttachedLevel();
		level->addParticle(new cParticleSense);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense.cfg");
		level->getParticleLast()->setHeight(96);
		level->getParticleLast()->setX(entity->getX() + entity->getWidth() / 2 /*+ m_particleOffsetX*/ - 4);
		level->getParticleLast()->setY(entity->getY() + entity->getHeight() - level->getParticleLast()->getHeight()/2 + level->getParticleLast()->getOffsetY());
		
		float velX;
		if (entity->getIsFacingLeft()) {
			velX = -level->getParticleLast()->getVelocityX();
		} else {
			velX = level ->getParticleLast()->getVelocityX();
		}
		level->getParticleLast()->setVelocityX(velX);
		level->getParticleLast()->update(0.0f);

		level->addParticle(new cParticleSense);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense.cfg");
		level->getParticleLast()->setTimeToBeAlive(10);
		level->getParticleLast()->setHeight(64);
		level->getParticleLast()->setX(entity->getX() + entity->getWidth() / 2 /*+ m_particleOffsetX*/ + 4 - level->getParticleLast()->getWidth());
		level->getParticleLast()->setY(entity->getY() + entity->getHeight() - level->getParticleLast()->getHeight()/2 + level->getParticleLast()->getOffsetY());
		level->getParticleLast()->setVelocityX(-velX);
		level->getParticleLast()->update(0.0f);
	}

	if (entity->getAttachedLevel() != nullptr) {
		//std::cout << entity->getAttachedLevel()->getX() << "\n";
		//std::cout << entity->getLevelX() << "\n";
		if (entity->getIsFacingLeft() == true && entity->getLevelX() < -16) {
			//entity->setIsFacingLeft(false);
			entity->setX(entity->getAttachedLevel()->getNumColumns() * 16 - entity->getAttachedLevel()->getX());
			entity->setLevelX((float)(entity->getAttachedLevel()->getNumColumns() * 16));
		}	
		if (entity->getIsFacingLeft() == false && entity->getLevelX() > entity->getAttachedLevel()->getNumColumns()*16) {
			//entity->setIsFacingLeft(true);
			entity->setX(-entity->getAttachedLevel()->getX()-64);
			entity->setLevelX(-16.0f);
		}
	}

	if (entity->getNumHealth() <= 0) {
		entity->setState(new cEntityFlylingDeathState);
	}


	if (!entity->getIsAttacking()) {

		if (entity->getSenseCollidedLeft()) {
			if (entity->getLeftObject()->getIsDead() || entity->getLeftObject() == nullptr) {
				return;
			}
			entity->setIsFacingLeft(true);
			entity->clearSenseLeft();
			entity->setState(new cEntityFlylingChargeState);
			return;
		}
		if (entity->getSenseCollidedRight()) {
			if (entity->getRightObject()->getIsDead() || entity->getRightObject() == nullptr) {
				return;
			}
			entity->setIsFacingLeft(false);
			entity->clearSenseRight();
			entity->setState(new cEntityFlylingChargeState);
			return;
		}

		
	}





	entity->setTimerState(entity->getTimerState()+time);
	if (entity->getTimerState() > 500) {
		std::cout << "Flyling regained health" << "\n";
		entity->setTimerState(0);
		entity->setNumHealth(100);
	}
}