#include "EntityFlylingFlightState.h"
#include "EntityFlylingAttackState.h"
#include "EntityFlylingBounceState.h"
#include "EntityFlylingDeathState.h"
#include <iostream>
#include "Player.h"
#include <math.h>

cEntityFlylingBounceState::cEntityFlylingBounceState() {
	std::cout << "new cEntityFlylingBounceState" << "\n";
	m_secondCall = false;
}

cEntityFlylingBounceState::~cEntityFlylingBounceState() {

}

void cEntityFlylingBounceState::update(cApp *app, cEntity *entity, float time) {	
	if (m_secondCall == false) {
		m_secondCall = true;

		m_startPosX = entity->getX();
		m_startPosY = entity->getY();
		
		if (entity->getIsFacingLeft() == true) {
			entity->setVelocityX(5.0f*time);
		} else {
			entity->setVelocityX(-5.0f*time);
		}
		entity->setVelocityY(0.0f);

		//entity->setVelocityX((float)cos( entity->getDirection() * 3.141592f / 180) * 2.5f );
		//entity->setVelocityY((float)sin( entity->getDirection() * 3.141592f / 180) * 2.5f );

		//std::cout << (float)cos( entity->getDirection() * 3.141592f / 180) * 2.5f << "\n";
	}
	/*if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	}
	else {
		entity->setVelocityY( entity->getVelocityY() + entity->getFallAcc() );		
	}*/
			
	entity->setAnim(eAnimTag::bounce);

	entity->setVelocityY( sin(entity->getX() * 0.125f ) );

	if (entity->getVelocityX() <= -20.0f*time) {
		entity->setVelocityX(entity->getVelocityX() + 1.0f);
	}
	else if (entity->getVelocityX() >= 20.0f*time) {
		entity->setVelocityX(entity->getVelocityX() - 1.0f);
	}

	/*if(entity->getVelocityX() > 0.0f && entity->getX() > m_startPosX+8)
		entity->setVelocityX( -entity->getVelocityX() );
	else if(entity->getVelocityX() < 0.0f && entity->getX() < m_startPosX-8)
		entity->setVelocityX( -entity->getVelocityX() );*/

	/*if(entity->getX() > m_startPosX+8)
		entity->setX(m_startPosX+8);
	else if(entity->getX() < m_startPosX-8)
		entity->setX(m_startPosX-8);*/

	//entity->setVelocityY( sin(entity->getX() * 0.5f ) );
	//entity->setVelocityY( sin(entity->getX() * 0.5f ) );

	entity->setTimerState( entity->getTimerState() + time);

	if (entity->getTimerState() > 20.0f) {
		if (entity->getNumHealth() <= 0) {
			entity->setIsDead(true);
			entity->setIsAttacking(false);
			entity->setIsCharging(false);
			entity->setState(new cEntityFlylingDeathState);
		} else {
			entity->setTimerState(0);
			entity->setIsAttacking(false);
			entity->setIsCharging(false);
			entity->setIsFacingLeft(!entity->getIsFacingLeft());
			entity->setState(new cEntityFlylingFlightState);
		}
	}
}