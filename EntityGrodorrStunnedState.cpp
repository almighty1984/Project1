#include "EntityGrodorrStunnedState.h"
#include "EntityGrodorrIdleState.h"
#include "EntityGrodorrDeathState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityGrodorrStunnedState::cEntityGrodorrStunnedState() {
	m_secondCall = false;
}

cEntityGrodorrStunnedState::~cEntityGrodorrStunnedState() {

}

void cEntityGrodorrStunnedState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		entity->setTimerState(0);
		m_secondCall = true;
		entity->setIsDead(false);
		entity->setIsAttacking(false);
		//entity->setVelocityX(0.0f);
		//entity->setVelocityY(0.0f);
		entity->setTileOffsetX(0.0f);
		entity->setAnim(eAnimTag::stunned);

		//entity->stun(50);
		
	}
	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityGrodorrDeathState);
		//return;
	}
	//entity->setVelocityX(0.0f);

	if (entity->getIsOnGround()) {
		if (entity->getVelocityX() < 0.0f) {
			entity->addVelocityX(entity->getMoveDec());
		} else if (entity->getVelocityX() > 0.0f) {
			entity->addVelocityX(-entity->getMoveDec());
		}
	}

	/*if (entity->getVelocityY() >= 0.0f && entity->getVelocityY() <= entity->getFallAcc()) {
		entity->setVelocityX(0.0f);
	}*/
	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	} else {
		entity->addVelocityY(entity->getFallAcc());
	}	
		
	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() >= 40.0f) {
		//entity->clearSense();
		//entity->setVelocityX(0.0f);
		entity->setState(new cEntityGrodorrIdleState);
	}

}