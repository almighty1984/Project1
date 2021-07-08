#include "EntityFluganWalkState.h"
#include "EntityFluganChargeState.h"
#include "EntityFluganAttackState.h"
#include "EntityFluganDeathState.h"
#include "Player.h"
#include "SoundsManager.h"
#include "ParticleSenseFlugan.h"

cEntityFluganWalkState::cEntityFluganWalkState() {
	m_secondCall = false;
}

cEntityFluganWalkState::~cEntityFluganWalkState() {

}

void cEntityFluganWalkState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTimerState(0);
		entity->clearSenses();
		entity->setIsAttacking(false);
		
	}
	if (entity->getIsFacingLeft()) {
		entity->setVelocityX(-entity->getMoveVelocity());
	} else {
		entity->setVelocityX(entity->getMoveVelocity());
	}

	entity->setTimerSense(entity->getTimerSense() + time);

	// Don't sense anything if entity locked
	if (entity->getIsLocked()) {
		entity->setTimerSense(0.0f);
	}

	if (entity->getTimerSense() > 5.0f) {		
		entity->setTimerSense(0.0f);
		
		cLevel *level = entity->getAttachedLevel();

		level->addParticle(new cParticleSenseFlugan);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_flugan.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		//level->getParticleLast()->setTimeToBeAlive(20);

		float posX = entity->getMiddleX() - level->getParticleLast()->getWidth() / 2;
		float posY = entity->getY() + entity->getHeight() / 2 - level->getParticleLast()->getHeight() / 2 + level->getParticleLast()->getOffsetY();
		float levelPosX = entity->getLevelX() + entity->getWidth() / 2 - level->getParticleLast()->getWidth() / 2;
		float levelPosY = entity->getLevelY() + entity->getHeight() / 2 - level->getParticleLast()->getHeight() / 2 + level->getParticleLast()->getOffsetY();

		if (entity->getIsFacingLeft()) {
			//posX -= level->getParticleLast()->getWidth();
			//levelPosX -= level->getParticleLast()->getWidth();
			level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
		}

		level->getParticleLast()->setX(posX);
		level->getParticleLast()->setY(posY);
		
		level->getParticleLast()->setStartX(levelPosX);
		level->getParticleLast()->setStartY(levelPosY);
		level->getParticleLast()->setLevelX(levelPosX);
		level->getParticleLast()->setLevelY(levelPosY);
			
		level->getParticleLast()->update(0.0f);
	}

	if (!entity->getIsAttacking()) {
		//m_chargeTimer = 0;
		//std::cout << "new cEntityFluganChargeState" << "\n";
				
			if (entity->getSenseCollidedLeft()) {
				if (entity->getLeftObject() == nullptr
					||
					entity->getLeftObject()->getAnimTag() == eAnimTag::death
					||
					entity->getLeftObject()->getType().substr(0, 7) == "target_") {					
					return;
				}
				entity->clearSenseLeft();
				entity->setIsFacingLeft(true);
				entity->setState(new cEntityFluganChargeState);
			}
			if (entity->getSenseCollidedRight()) {
				if (entity->getRightObject() == nullptr
					||
					entity->getRightObject()->getAnimTag() == eAnimTag::death
					||
					entity->getRightObject()->getType().substr(0, 7) == "target_") {					
					return;
				}
				entity->clearSenseRight();
				entity->setIsFacingLeft(false);
				entity->setState(new cEntityFluganChargeState);
			}

	}

	//if (entity->getAttachedPlayer() != nullptr) {
	//	float pointX = (entity->getX() + entity->getWidth() / 2) - (entity->getAttachedPlayer()->getX() + entity->getAttachedPlayer()->getWidth() / 2);
	//	float pointY = (entity->getY() + entity->getHeight() / 2) - (entity->getAttachedPlayer()->getY() + entity->getAttachedPlayer()->getHeight() / 2);
	//	//std::cout /*<< pointX << " "*/ << abs(pointY) << "\n";
	//	/*if (pointX < 0.0f) {
	//		entity->setIsFacingLeft(false);
	//	}
	//	else {
	//		entity->setIsFacingLeft(true);
	//	}*/
	//	if (((pointX > 0 && pointX <= 128.0f && entity->getIsFacingLeft()) || (pointX < 0 && pointX >= -128.0f && !entity->getIsFacingLeft()))
	//		&& entity->getAttachedPlayer()->getVitalityMeterValue() > 0	&& abs(pointY) <= 32.0f) {

	//		//if (( entity->getY() < entity->getAttachedPlayer()->getY() && entity->getAttachedPlayer()->getY() - entity->getY() < 64) || ( entity->getY() > entity->getAttachedPlayer()->getY() && entity->getY() - entity->getAttachedPlayer()->getY() < 64) )  {
	//			//if ( (entity->getX()+32 < entity->getAttachedPlayer()->getX()+64) && abs((int)(entity->getAttachedPlayer()->getX()+64 - entity->getX()+32)) < 256-64 && !entity->getIsFacingLeft() ||	(entity->getX()+32 > entity->getAttachedPlayer()->getX()+64) && abs(entity->getX()+32 - entity->getAttachedPlayer()->getX()+64) < 256 && entity->getIsFacingLeft()	) {
	//			//if((entity->getX()+32)-(entity->getAttachedPlayer()->getX()+64) < 64) {
	//		if (entity->getIsCharging() == false && entity->getIsAttacking() == false
	//			&& entity->getAttachedPlayer()->getIsDead() == false) {
	//			//m_chargeTimer = 0;
	//			//std::cout << "new cEntityFluganChargeState" << "\n";
	//			entity->setState(new cEntityFluganChargeState);
	//			entity->setIsCharging(true);
	//			entity->setIsAttacking(false);
	//			entity->setTimerState(0);

	//			cSoundsManager::play(eSoundTag::fluganCharge);
	//		}
	//		//}			
	//	}
	//	/*else {
	//		if(m_isMeleeing == true && m_timerState > 200) {
	//			std::cout << "new cEntityFluganWalkState" << "\n";
	//			setState(new cEntityFluganWalkState);
	//			m_isCharging = false;
	//			m_isMeleeing = false;
	//			m_timerState = 0;
	//		}
	//	}*/
	//}

	if (entity->getVelocityX() >= 0.0f) {
		entity->setIsFacingLeft(false);
	} else {
		entity->setIsFacingLeft(true);
	}

	if (entity->getVelocityX() >= entity->getMoveVelocity()) {
		entity->setVelocityX(entity->getMoveVelocity());
	} else if (entity->getVelocityX() <= -entity->getMoveVelocity()) {
		entity->setVelocityX(-entity->getMoveVelocity());
	}

	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	} else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc());
	}
	
	//entity->m_tileOffsetY = entity->m_animWalk.y;
	//entity->m_animSpeed = entity->m_animWalk.speed;
	
	entity->setAnim(eAnimTag::walk);
	
	//// Update animation	
	//if (entity->getAnimTime() >= 10) {
	//	entity->setTileOffsetX( entity->getTileOffsetX() + entity->getWidth() );

	//	if (entity->getTileOffsetX() >= (entity->getWidth()*entity->getNumAnimFrames()) ) {
	//		if (entity->getCurrentLoops() < entity->getNumAnimLoops() && entity->getNumAnimLoops() != 0) {
	//			//entity->m_tileOffsetX = 0;
	//			entity->setTileOffsetX( (float)(entity->getWidth()*entity->getNumAnimFrames()) );
	//			entity->setCurrentLoops( entity->getCurrentLoops() + 1 );
	//		}
	//		if (entity->getNumAnimLoops() == 0) {
	//			entity->setTileOffsetX(0.0f);
	//			entity->setCurrentLoops(0);
	//		}
	//	}
	//	entity->setAnimTime(0.0f);
	//} else { 		
	//	entity->setAnimTime( entity->getAnimTime() + entity->getAnimSpeed());
	//}

	//if (entity->getTileOffsetX() >= (entity->getWidth()*entity->getNumAnimFrames())-entity->getWidth() ) {
	//	entity->setTileOffsetX( (float)(entity->getWidth() * entity->getNumAnimFrames() - entity->getWidth()) );
	//}

	if (entity->getIsAttacking() == true) {
		entity->setState(new cEntityFluganAttackState);
		entity->setIsCharging(false);
		entity->setIsAttacking(false);
	}

	

	if (entity->getNumHealth() <= 0) {		
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFluganDeathState);
	}	
}