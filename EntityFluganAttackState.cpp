#include "EntityFluganAttackState.h"
#include "EntityFluganWalkState.h"
#include "EntityFluganDeathState.h"
#include <iostream>
#include "Player.h"
#include "SoundsManager.h"
#include "ParticleFluganAttack.h"

void cEntityFluganAttackState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		std::cout << "cEntityFluganAttackState\n";
		entity->setTimerState(0.0f);
		entity->setIsCharging(false);
		entity->setIsAttacking(true);		
		entity->setVelocityX(0.0f);	
		cSoundsManager::stop(eSoundTag::fluganAttack);
		cSoundsManager::play(eSoundTag::fluganAttack);		
	}



	entity->setTimerSense(entity->getTimerSense() + time);
	if (entity->getTimerSense() > 5.0f) {
		entity->setTimerSense(0.0f);
		cLevel *level = entity->getAttachedLevel();
		if (level == nullptr) { return; }
		level->addParticle(new cParticleFluganAttack);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_flugan_attack.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());

		float posX = entity->getMiddleX();
		float posY = entity->getY() + entity->getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY();
		float levelPosX = entity->getLevelX() + entity->getWidth() / 2;
		float levelPosY = entity->getLevelY() + entity->getHeight() / 2 - level->getParticleLast()->getHeight() / 2;
		

		if (entity->getIsFacingLeft()) {
			level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
			posX -= level->getParticleLast()->getWidth();
			posX -= level->getParticleLast()->getOffsetX();
			//posX += 8;
			levelPosX -= level->getParticleLast()->getWidth();
			levelPosX -= level->getParticleLast()->getOffsetX();
		} else {
			posX += level->getParticleLast()->getOffsetX();
			//posX -= 8;
			levelPosX += level->getParticleLast()->getOffsetX();
		}
		level->getParticleLast()->setX(posX);
		level->getParticleLast()->setY(posY);
		level->getParticleLast()->setStartX(levelPosX);
		level->getParticleLast()->setStartY(levelPosY);
		level->getParticleLast()->setLevelX(levelPosX);
		level->getParticleLast()->setLevelY(levelPosY);
		
		level->getParticleLast()->update(0.0f);
	}

	entity->setAnim(eAnimTag::attack);
	float velX = 3.5f;
	if (entity->getIsHurting()) {
		velX = 1.75f;
	}
	if (entity->getIsFacingLeft()) {
		entity->setVelocityX(-velX);
	} else {
		entity->setVelocityX(velX);
	}

	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
	} else {
		entity->setVelocityY( entity->getVelocityY() + entity->getFallAcc());
	}

	//// Update animation	
	//if (entity->getAnimTime() >= 10.0f) {
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

	entity->setTimerState( entity->getTimerState() + time);

	if (entity->getTimerState() > 50.0f && !entity->getAttachedPlayer()->getIsRiding()) {
		entity->setIsAttacking(false);
		entity->setIsCharging(false);				
		entity->setState(new cEntityFluganWalkState);
		return;
	}

	if (entity->getNumHealth() <= 0) {
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFluganDeathState);
	}
	
}