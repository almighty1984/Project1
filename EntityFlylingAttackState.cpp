#include "EntityFlylingFlightState.h"
#include "EntityFlylingAttackState.h"
#include "EntityFlylingBounceState.h"
#include "EntityFlylingDeathState.h"
#include <iostream>
#include "Player.h"
#include <math.h>

cEntityFlylingAttackState::cEntityFlylingAttackState() {
	std::cout << "new cEntityFlylingAttackState" << "\n";
	m_secondCall = false;
}

cEntityFlylingAttackState::~cEntityFlylingAttackState() {

}

void cEntityFlylingAttackState::update(cApp *app, cEntity *entity, float time) {	
	if (m_secondCall == false) {
		m_secondCall = true;
		
		entity->setVelocityX((float)cos( entity->getDirection() * 3.141592f / 180) * 5.0f );
		entity->setVelocityY((float)sin( entity->getDirection() * 3.141592f / 180) * 5.0f );

		//std::cout << (float)cos( entity->getDirection() * 3.141592f / 180) * 2.5f << "\n";
	}
	/*if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	}
	else {
		entity->setVelocityY( entity->getVelocityY() + entity->getFallAcc() );		
	}*/
			
	entity->setIsAttacking(true);
	entity->setIsCharging(false);

	entity->setAnim(eAnimTag::attack);

	entity->setTimerState( entity->getTimerState() + 1);

	if (entity->getTimerState() > 40) {
		entity->setTimerState(0);
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFlylingFlightState);		
	}

	if (entity->getNumHealth() <= 0) {
		entity->setIsDead(true);
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFlylingDeathState);
	}
}