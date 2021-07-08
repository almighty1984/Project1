#include "EntityFluganChargeState.h"
#include "EntityFluganAttackState.h"
#include "EntityFluganDeathState.h"
#include "SoundsManager.h"

cEntityFluganChargeState::cEntityFluganChargeState() {
	m_secondCall = false;
}

void cEntityFluganChargeState::update(cApp *app, cEntity *entity, float time) {	
	/*if(entity->getIsFacingLeft() == false) {
		entity->setVelocityX(2.0f);
	}
	else {
		entity->setVelocityX(-2.0f);
	}*/

	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTimerState(0.0f);
		entity->setIsCharging(true);
		entity->setIsAttacking(false);		
		entity->setVelocityX(0.0f);
		entity->setAnim(eAnimTag::idle);
		cSoundsManager::play(eSoundTag::fluganCharge);
	}	
	
	entity->setTimerState( entity->getTimerState() + time);

	if (entity->getTimerState() > 20.0f) {
		entity->setTimerState(0.0f);
		entity->setIsAttacking(true);
		entity->setIsCharging(false);
		entity->setState(new cEntityFluganAttackState);
	}

	if (entity->getNumHealth() <= 0) {
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFluganDeathState);
	}
}