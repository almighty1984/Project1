#include "EntityPiganBounceState.h"
#include "EntityPiganBackState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityPiganBounceState::cEntityPiganBounceState() {
	m_secondCall = false;
}

cEntityPiganBounceState::~cEntityPiganBounceState() {

}

void cEntityPiganBounceState::update(cApp* app, cEntity* entity, float time) {
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
	entity->setIsOnBack(true);
	entity->setVelocityX(0.0f);


	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() >= 20.0f) {
		//entity->setTimerState(50);
		entity->setVelocityX(0.0f);
		entity->setState(new cEntityPiganBackState);
	}

}