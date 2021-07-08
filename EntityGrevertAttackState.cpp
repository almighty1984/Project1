#include "EntityGrevertAttackState.h"
#include "EntityGrevertDeathState.h"
#include "EntityGrevertHideState.h"
#include "SoundsManager.h"
#include "Player.h"
#include "ParticleGrevertAttack.h"
#include "ParticleGrevertBounce.h"

cEntityGrevertAttackState::cEntityGrevertAttackState() {
	m_secondCall = false;
}

void cEntityGrevertAttackState::update(cApp *app, cEntity *entity, float time) {	
	//if (entity->getNumHealth() <= 0) {
	//	entity->setAnimCurrent(entity->getAnimDeath());
	//	entity->setTileOffsetX(0.0f);
	//	entity->setState(new cEntityGrodorrDeathState);
	//	//return;
	//}
	//else {
		//entity->setAnim(eAnimTag::attack);
	//}
	
	cLevel* level = entity->getAttachedLevel();

	if (!m_secondCall) {
		m_secondCall = true;

		entity->setMoveAcc(entity->getStartMoveAcc());
		entity->setMoveDec(entity->getStartMoveDec());
		entity->setMoveVelocity(entity->getStartMoveVelocity());



		entity->setIsIdle(false);
		entity->setIsStunned(false);
		entity->setIsAttacking(false);
		entity->setIsHidden(false);
		entity->setTileOffsetX(0.0f);
		entity->setAnimTime(0);
		entity->setTimerState(0.0f);
		entity->setAnim(eAnimTag::hide);





		
		level->addParticle(new cParticleGrevertBounce);
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_grevert_bounce.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		level->getParticleLast()->setDoGravitate(false);
		level->getParticleLast()->setX(entity->getMiddleX() - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setY(entity->getBottom());

		level->getParticleLast()->setLevelX(entity->getLevelX() + entity->getWidth()/2 - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setLevelY(entity->getLevelY() + entity->getHeight() / 2 - level->getParticleLast()->getHeight() / 2);

		std::cout << "EntityGrevertAttackState getting ready\n";
	}	
	entity->setVelocityX(0.0f);

	// Wait a while before attacking
	if (entity->getTimerState() > 20.0f && !entity->getIsAttacking()) {
		entity->setIsAttacking(true);
		entity->setAnim(eAnimTag::attack);
		entity->setTileOffsetX(0.0f);


		
				
		cSoundsManager::stop(eSoundTag::fluganCharge);;
		cSoundsManager::play(eSoundTag::fluganCharge);

		level->addParticle(new cParticleGrevertAttack);

		/*cObject *pObj;
		pObj = static_cast<cObject*>(entity);*/

		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_grevert_attack.cfg");
		level->getParticleLast()->setDoGravitate(false);

		if (entity->getIsFacingLeft()) {
			level->getParticleLast()->setX(entity->getX() + entity->getWidth() / 2 /*+ m_particleOffsetX*/ - 8 - level->getParticleLast()->getWidth());
			level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
		} 		else {
			level->getParticleLast()->setX(entity->getX() + entity->getWidth() / 2 /*+ m_particleOffsetX*/ + 8);
		}
		level->getParticleLast()->setVelocityY(0.0f);
		level->getParticleLast()->setY(entity->getY() + entity->getHeight() - level->getParticleLast()->getHeight());

		level->getParticleLast()->setLevelX(entity->getLevelX() + entity->getWidth() / 2 - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setLevelY(entity->getLevelY() + entity->getHeight() / 2 - level->getParticleLast()->getHeight() / 2);
	}


	if (entity->getTimerState() > 60.0f/* && !entity->getSenseCollided()*/) {
		entity->setTimerState(0.0f);
		entity->setIsAttacking(false);





		//entity->setVelocityY(-5.0f);

		//cSoundsManager::stop(eSoundTag::jump);
		//cSoundsManager::play(eSoundTag::jump);

		/*cSoundsManager::m_soundFluganAttack.stop();
		cSoundsManager::m_soundFluganAttack.play();*/

		entity->setState(new cEntityGrevertHideState);
	}


	entity->setTimerState(entity->getTimerState() + time);
}