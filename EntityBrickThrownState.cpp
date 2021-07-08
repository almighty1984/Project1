#include "EntityBrickDeathState.h"
#include "EntityBrickIdleState.h"
#include "EntityBrickThrownState.h"

#include <iostream>

cEntityBrickThrownState::cEntityBrickThrownState() {
	m_secondCall = false;
}

cEntityBrickThrownState::~cEntityBrickThrownState() {

}

void cEntityBrickThrownState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		std::cout << "cEntityBrickThrownState\n";

		entity->setIsHidden(false);
		entity->setIsSolid(true);

		entity->setIsThrown(true);
		entity->setIsStatic(false);
		entity->setIsCarried(false);		

		entity->setTimerState(0.0f);		
	}

	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	} else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc()/* */);
	}

	//entity->setTimerState(entity->getTimerState() + time);

	//if (entity->getTimerState() >= entity->getTimeToBeDead() && entity->getTimeToBeDead() != 0.0f) {
	//	entity->setTimerState(0);
	//	entity->setVelocityX(0.0f);
	//	//entity->setIsDead(true);
	//	entity->setState(new cEntityBrickIdleState);
	//}

}