#include "EntityFlylingHitState.h"
#include "EntityFlylingFlightState.h"
#include "EntityFlylingDeathState.h"
#include "SoundsManager.h"

#include <math.h>

cEntityFlylingHitState::cEntityFlylingHitState() {
	m_secondCall = false;
	m_velX = m_velY = 0.0f;
}

cEntityFlylingHitState::cEntityFlylingHitState(float velX, float velY) {
	m_secondCall = false;
	m_velY = velY;
	m_velX = velX;
}

cEntityFlylingHitState::~cEntityFlylingHitState() {
	m_secondCall = false;
	m_velX = m_velY = 0.0f;
}

void cEntityFlylingHitState::update(cApp *app, cEntity *entity, float time) {
	if (m_secondCall == false) {
		m_secondCall = true;

		entity->setVelocityY(m_velY);


		std::cout << entity->getNumHealth() << "\n";
		entity->clearSenses();
		//if (entity->getNumHealth() <= 0) {
		//	//entity->setIsDead(true);
		//	entity->setIsAttacking(false);
		//	entity->setIsCharging(false);
		//	entity->setState(new cEntityFlylingDeathState);
		//	return;
		//}
		//entity->setIsDead(true); 
		cSoundsManager::stop(eSoundTag::flylingAttack);
		cSoundsManager::stop(eSoundTag::flylingHurt);
		cSoundsManager::play(eSoundTag::flylingHurt);
		 
		//bool tmpBool = entity->getIsFacingLeft();
		entity->setTimerState(0.0f);
		//if (entity->getIsFacingLeft() == true) {
		//	entity->setVelocityX(4.5f);
		//	//entity->setIsFacingLeft(false);
		//} else {
		//	entity->setVelocityX(-4.5f);
		//	//entity->setIsFacingLeft(true);
		//}
		//entity->setVelocityY(2.5f);
		std::cout << "cEntityFlylingHitState\n";
	}


	/*if (entity->getVelocityX() < 0.0f) {
		entity->setIsFacingLeft(true);
	} else {
		entity->setIsFacingLeft(false);
	}*/

	std::cout << "HIT STATE" << "\n";
	entity->setIsHurting(true);
	entity->setAnim(eAnimTag::bounce);

	

	//entity->setVelocityY(sin(entity->getLevelX()*0.25f) * 6 + 0.0f);

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 15.0f) {
		//entity->setNumHealth(entity->getStartHealth());
		entity->setState(new cEntityFlylingFlightState);		
	}	
}