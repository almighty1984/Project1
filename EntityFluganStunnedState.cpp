#include "EntityFluganStunnedState.h"
#include "EntityFluganChargeState.h"
#include "EntityFluganDeathState.h"
#include "Player.h"
#include "SoundsManager.h"

cEntityFluganStunnedState::cEntityFluganStunnedState() {
	m_secondCall = false;
}

cEntityFluganStunnedState::~cEntityFluganStunnedState() {

}

void cEntityFluganStunnedState::update(cApp *app, cEntity *entity, float time) {
	if (m_secondCall == false) {
		m_secondCall = true;
		entity->setTimerState(0.0f);
		//entity->setVelocityX(0.0f);
		//entity->setVelocityY(-2.5f);
		entity->setIsStunned(true);
		entity->setIsAttacking(false);

		//entity->stun(50);
	}
	//// Regenerate health
	//if (entity->getNumHealth() < entity->getStartHealth()) {
	//	entity->setNumHealth(entity->getNumHealth() + 0.05f);
	//}
	//if (entity->getNumHealth() > entity->getStartHealth()) {
	//	entity->setNumHealth(entity->getStartHealth());
	//}
	if (entity->getVelocityY() >= 0.0f && entity->getVelocityY() <= entity->getFallAcc()) {
		entity->setVelocityX(0.0f);
	}

	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	}
	else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}

	//entity->m_tileOffsetY = entity->m_animWalk.y;
	//entity->m_animSpeed = entity->m_animWalk.speed;

	entity->setAnim(eAnimTag::stunned);

	//// Update animation	
	//if (entity->getAnimTime() >= 10.0f) {
	//	entity->setTileOffsetX(entity->getTileOffsetX() + entity->getWidth());

	//	if (entity->getTileOffsetX() >= (entity->getWidth() * entity->getNumAnimFrames())) {
	//		if (entity->getCurrentLoops() < entity->getNumAnimLoops() && entity->getNumAnimLoops() != 0) {
	//			//entity->m_tileOffsetX = 0;
	//			entity->setTileOffsetX((float)(entity->getWidth() * entity->getNumAnimFrames()));
	//			entity->setCurrentLoops(entity->getCurrentLoops() + 1);
	//		}
	//		if (entity->getNumAnimLoops() == 0) {
	//			entity->setTileOffsetX(0.0f);
	//			entity->setCurrentLoops(0);
	//		}
	//	}
	//	entity->setAnimTime(0.0f);
	//}
	//else {
	//	entity->setAnimTime(entity->getAnimTime() + entity->getAnimSpeed());
	//}

	//if (entity->getTileOffsetX() >= (entity->getWidth() * entity->getNumAnimFrames()) - entity->getWidth()) {
	//	entity->setTileOffsetX((float)(entity->getWidth() * entity->getNumAnimFrames() - entity->getWidth()));
	//}

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 20.0f/* && entity->getVelocityY() >= 0.0f && entity->getVelocityY() <= entity->getFallAcc()*/) {
		entity->setState(new cEntityFluganChargeState);
	}


	if (entity->getNumHealth() <= 0) {
		entity->setIsDead(true);
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFluganDeathState);
	}
}