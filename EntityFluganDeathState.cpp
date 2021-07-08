#include "EntityFluganDeathState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityFluganDeathState::cEntityFluganDeathState() {
	m_secondCall = false;
}

cEntityFluganDeathState::~cEntityFluganDeathState() {

}

void cEntityFluganDeathState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {		
		m_secondCall = true;
		entity->setHurtAgainDelayValue(100);
		entity->setTimerState(0.0f);
		entity->setIsDead(false);
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);
		entity->setTileOffsetX(0.0f);
	}
	/*if (entity->getVelocityY() >= 0.0f && entity->getVelocityY() <= entity->getFallAcc()) {
		entity->setVelocityX(0.0f);
	}
	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	}
	else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}*/
	entity->setAnim(eAnimTag::death);

	//// Update animation	
	//if (entity->getAnimTime() > 10) {
	//	entity->setTileOffsetX(entity->getTileOffsetX() + entity->getWidth());

	//	if (entity->getTileOffsetX() >= (entity->getWidth() * entity->getNumAnimFrames())) {
	//		if (entity->getCurrentLoops() < entity->getNumAnimLoops() && entity->getNumAnimLoops() != 0) {
	//			//entity->m_tileOffsetX = 0;
	//			entity->setTileOffsetX((float)entity->getWidth() * entity->getNumAnimFrames());
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
	//	entity->setTileOffsetX((float)entity->getWidth() * entity->getNumAnimFrames() - entity->getWidth());
	//}


	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() >= 20.0f) {
		entity->setIsDead(true);
	}

}