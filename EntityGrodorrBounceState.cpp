#include "EntityGrodorrBounceState.h"
#include "EntityGrodorrStunnedState.h"
#include "EntityGrodorrDeathState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityGrodorrBounceState::cEntityGrodorrBounceState() {
	m_secondCall = false;
}

cEntityGrodorrBounceState::~cEntityGrodorrBounceState() {

}

void cEntityGrodorrBounceState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTimerState(0);		
		cSoundsManager::stop(eSoundTag::bounce);
		cSoundsManager::play(eSoundTag::bounce);
		entity->setIsDead(false);
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);
		entity->setTileOffsetX(0.0f);
		entity->setAnim(eAnimTag::bounce);
	}
	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityGrodorrDeathState);
		//return;
	}
	entity->setVelocityX(0.0f);

	if (entity->getVelocityY() >= 0.0f && entity->getVelocityY() <= entity->getFallAcc()) {
		entity->setVelocityX(0.0f);
	}
	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	}
	else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}
	
	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 20.0f) {
		//entity->setTimerState(50);
		entity->setVelocityX(0.0f);
		entity->setState(new cEntityGrodorrStunnedState);
	}

}