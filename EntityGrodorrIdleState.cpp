#include "EntityGrodorrIdleState.h"
#include "EntityGrodorrAttackState.h"
#include "EntityGrodorrDeathState.h"
#include "EntityGrodorrJumpState.h"
#include "Player.h"
#include "SoundsManager.h"

#include "ParticleSenseGrodorr.h"


cEntityGrodorrIdleState::cEntityGrodorrIdleState() {
	m_secondCall = false;
}

cEntityGrodorrIdleState::~cEntityGrodorrIdleState() {

}

void cEntityGrodorrIdleState::update(cApp *app, cEntity *entity, float time) {
	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityGrodorrDeathState);
		//return;
	} else {
		entity->setAnim(eAnimTag::idle);
	}
	entity->setVelocityX(0.0f);
	if (!m_secondCall) {
		entity->clearSenses();
		entity->setIsStunned(false);
		entity->setTimerState(0.0f);
		entity->setTimerSense(0.0f);
		m_secondCall = true;
		entity->setIsDead(false);
		entity->setVelocityX(0.0f);
		//entity->setVelocityY(0.0f);
	}
	
	entity->setTimerSense(entity->getTimerSense() + time);
	//entity->setTimerSenseClear(entity->getTimerSenseClear() + time);

	// Don't sense anything if entity locked
	if (entity->getIsLocked()) {
		entity->setTimerSense(0.0f);
	}

	if (entity->getTimerSense() > 1.0f) {
		entity->setTimerSense(0.0f);
		entity->spawnSenses();
	}

	/*if (entity->getTimerSenseClear() > 1.0f) {
		entity->setTimerSenseClear(0.0f);
		entity->clearSenses();
	}*/

	if (!entity->getIsAttacking()) {
		if (entity->getSenseCollidedLeft()) {
			if (entity->getLeftObject()->getIsDead() || entity->getLeftObject() == nullptr) {
				return;
			}			
			entity->setIsFacingLeft(true);
			if (entity->getAttachedPlayer()->getIsSliding()) {
				entity->setState(new cEntityGrodorrJumpState);				
			} else {
				entity->setState(new cEntityGrodorrAttackState);
			}
			return;
		}
		if (entity->getSenseCollidedRight()) {
			if (entity->getRightObject()->getIsDead() || entity->getRightObject() == nullptr) {
				return;
			}
			entity->setIsFacingLeft(false);
			if (entity->getAttachedPlayer()->getIsSliding()) {
				entity->setState(new cEntityGrodorrJumpState);
			} else {
				entity->setState(new cEntityGrodorrAttackState);				
			}
			return;
		}

		
	}

	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	} else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}	
		
	entity->setTimerState(entity->getTimerState() + time);
	
	if (entity->getTimerState() > 500 + rand() % 500) {
		//if (entity->getVelocityY() == 0.0f) {
			entity->setTimerState(0.0f);
			entity->setIsAttacking(false);
			//entity->setVelocityY(-5.0f);

			//cSoundsManager::stop(eSoundTag::jump);
			//cSoundsManager::play(eSoundTag::jump);

			/*cSoundsManager::m_soundFluganAttack.stop();
			cSoundsManager::m_soundFluganAttack.play();*/

			entity->setState(new cEntityGrodorrJumpState);
		//}
	}
}