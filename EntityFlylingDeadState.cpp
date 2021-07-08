#include "EntityFlylingHitState.h"
#include "EntityFlylingFlightState.h"
#include "SoundsManager.h"

#include <math.h>

cEntityFlylingHitState::cEntityFlylingHitState() {
	m_secondCall = false;
}

cEntityFlylingHitState::~cEntityFlylingHitState() {

}

void cEntityFlylingHitState::update(float time, cEntity* entity) {
	if (m_secondCall == false) {
		m_secondCall = true;
		entity->setFlags(0);
		entity->setIsDead(true); 
		cSoundsManager::get().m_soundFlylingAttack.stop();
		cSoundsManager::get().m_soundFlylingHurt.stop();
		cSoundsManager::get().m_soundFlylingHurt.play();
		 
		//bool tmpBool = entity->getFacingLeft();
		entity->setStateTimer(0);
		//if (entity->getFacingLeft() == true) {
		//	entity->setVelocityX(4.5f);
		//	//entity->setFacingLeft(false);
		//} else {
		//	entity->setVelocityX(-4.5f);
		//	//entity->setFacingLeft(true);
		//}
		//entity->setVelocityY(2.5f);
		std::cout << "cEntityFlylingHitState\n";
	}

	entity->setIsHurting(true);
	entity->setAnimCurrent(entity->getAnimDeath());

	entity->setVelocityY(sin(entity->getLevelPositionX()*0.25f) * 4 + 0.0f);

	// Set current animation
	entity->setTileOffsetY(entity->getAnimCurrent().y);
	entity->setAnimationSpeed(entity->getAnimCurrent().speed);
	entity->setAnimationLoops(entity->getAnimCurrent().loop);

	// Update animation	
	if (entity->getAnimationTime() > 10) {
		entity->setTileOffsetX(entity->getTileOffsetX() + entity->getWidth());

		if (entity->getTileOffsetX() >= (entity->getWidth()*entity->getNumFrames())) {
			if (entity->getCurrentLoops() < entity->getAnimationLoops() && entity->getAnimationLoops() != 0) {
				//entity->m_tileOffsetX = 0;
				entity->setTileOffsetX((float)entity->getWidth()*entity->getNumFrames());
				entity->setCurrentLoops(entity->getCurrentLoops() + 1);
			}
			if (entity->getAnimationLoops() == 0) {
				entity->setTileOffsetX(0.0f);;
				entity->setCurrentLoops(0);
			}
		}

		entity->setAnimationTime(0.0f);
	}
	else {
		entity->setAnimationTime(entity->getAnimationTime() + entity->getAnimationSpeed());
	}

	if (entity->getTileOffsetX() >= (entity->getWidth()*entity->getNumFrames()) - entity->getWidth()) {
		entity->setTileOffsetX((float)(entity->getWidth() * entity->getNumFrames() - entity->getWidth()));
	}

	entity->setStateTimer(entity->getStateTimer() + 1);

	if (entity->getStateTimer() > 20) {
		entity->setStateTimer(0);
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setIsDead(false);

		entity->setNumHealth(entity->getStartHealth());

		entity->setState(new cEntityFlylingFlightState);
	}
}