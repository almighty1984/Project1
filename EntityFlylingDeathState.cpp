#include "EntityFlylingDeathState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityFlylingDeathState::cEntityFlylingDeathState() {
	m_secondCall = false;
}

cEntityFlylingDeathState::~cEntityFlylingDeathState() {

}

void cEntityFlylingDeathState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		entity->setTimerState(0.0f);
		m_secondCall = true;
		entity->setIsDead(false);
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);
		entity->setTileOffsetX(0.0f);
	}

	/*if (entity->getVelocityY() >= 0.0f && entity->getVelocityY() <= entity->getFallAcc()) {
		entity->setVelocityX(0.0f);
	}
	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	}
	else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}*/
	entity->setAnim(eAnimTag::death);

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() >= 5.0f) {
		entity->setTimerState(5.0f);
		entity->setVelocityX(0.0f);
		entity->setIsDead(true);
	}
}