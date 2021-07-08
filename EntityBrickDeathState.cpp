#include "EntityBrickDeathState.h"
#include "EntityBrickIdleState.h"
#include <iostream>

cEntityBrickDeathState::cEntityBrickDeathState() {
	m_secondCall = false;
}

cEntityBrickDeathState::~cEntityBrickDeathState() {

}

void cEntityBrickDeathState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		std::cout << "cEntityBrickDeathState\n";

		entity->setIsDead(true);
		entity->setIsHidden(true);
		entity->setIsSolid(false);

		entity->setTimeBeingDead(0.0f);
		
		entity->setIsHiddenMeterHealth(true);
		entity->setHurtAgainDelayValue(100);
		entity->setTimerState(0.0f);
		
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);
		entity->setTileOffsetX(0.0f);

	}

	

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() >= entity->getTimeToBeDead() && entity->getTimeToBeDead() != 0.0f) {
		entity->setTimerState(0);
		entity->setVelocityX(0.0f);
		entity->setIsDead(false);
		entity->setNumHealth(1.0f);
		entity->setState(new cEntityBrickIdleState);
	}

}