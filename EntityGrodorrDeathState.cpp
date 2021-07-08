#include "EntityGrodorrDeathState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityGrodorrDeathState::cEntityGrodorrDeathState() {
	m_secondCall = false;
}

cEntityGrodorrDeathState::~cEntityGrodorrDeathState() {
	m_secondCall = false;
}

void cEntityGrodorrDeathState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTimerState(0.0f);
		cSoundsManager::stop(eSoundTag::collidedFlugan);
		cSoundsManager::play(eSoundTag::collidedFlugan);
		entity->setIsSolid(false);
		entity->setIsHiddenMeterHealth(true);
		entity->setHurtAgainDelayValue(100);
		
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);
		entity->setTileOffsetX(0.0f);

	}

	/*if (entity->getTimerState() >= 50.0f) {
		return;
	}*/

	//entity->setTimerState(entity->getTimerState() + time);

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
}