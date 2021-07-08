#include "EntityGrodorrAttackState.h"
#include "EntityGrodorrJumpState.h"
#include "EntityGrodorrDeathState.h"
#include "SoundsManager.h"
#include "Player.h"
#include "ParticleGrodorrAttack.h"

cEntityGrodorrAttackState::cEntityGrodorrAttackState()
{
	m_secondCall = false;
}

cEntityGrodorrAttackState::~cEntityGrodorrAttackState()
{

}

void cEntityGrodorrAttackState::update(cApp *app, cEntity *entity, float time) {
	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityGrodorrDeathState);
		//return;
	} else {
		entity->setAnim(eAnimTag::attack);
	}
	if (!m_secondCall) {
		cSoundsManager::stop(eSoundTag::fluganCharge);
		cSoundsManager::play(eSoundTag::fluganCharge);
		entity->setIsStunned(false);
		entity->setIsAttacking(true);
		m_secondCall = true;
		entity->setTileOffsetX(0.0f);
		entity->setAnimTime(0);
		entity->setTimerState(0.0f);

		cLevel* level = entity->getAttachedLevel();
		level->addParticle(new cParticleGrodorrAttack);
		
		level->getParticleLast()->attachParent(entity);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_grodorr_attack.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		
		float posX;
		
		if (entity->getIsFacingLeft()) {
			posX = (float)(entity->getWidth() / 2 /*+ m_particleOffsetX*/ + 24 - level ->getParticleLast()->getWidth());
			level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
		} else {
			posX = (float)(entity->getWidth() / 2 /*+ m_particleOffsetX*/ - 24);
			//m_particles.at(m_particles.size()-1)->setVelocityX(/*getVelocityX()+3.0f*/);
		}
		level->getParticleLast()->setX(entity->getX() + posX);
		level->getParticleLast()->setLevelX(entity->getLevelX() + posX);	
		level->getParticleLast()->setStartX(entity->getStartX() + posX);


		float posY = (float)(entity->getHeight() - level->getParticleLast()->getHeight());
		level->getParticleLast()->setY(entity->getY() + posY);
		level->getParticleLast()->setLevelY(entity->getLevelY() + posY);
		level->getParticleLast()->setStartY(entity->getStartY() + posY);
		level->getParticleLast()->update(0.0f);

		//cRenderingManager::addParticle(l->getParticleLast());

		//entity->m_particles.push_back(new cParticleGrodorr);

		//entity->m_particles.at(entity->m_particles.size() - 1)->attachParent(entity);
		//entity->m_particles.at(entity->m_particles.size() - 1)->loadConfig("Data\\Particles\\p_grodorr.cfg");
		////entity->m_particles.at(entity->m_particles.size() - 1)->setIsHidden(false);
		//if (entity->getIsFacingLeft()) {
		//	entity->m_particles.at(entity->m_particles.size() - 1)->setX(entity->getX() + entity->getWidth() / 2 /*+ m_particleOffsetX*/ + 16 - entity->m_particles.at(entity->m_particles.size() - 1)->getWidth());
		//	entity->m_particles.at(entity->m_particles.size() - 1)->setVelocityX(-entity->m_particles.at(entity->m_particles.size() - 1)->getVelocityX());
		//}
		//else {
		//	entity->m_particles.at(entity->m_particles.size() - 1)->setX(entity->getX() + entity->getWidth() / 2 /*+ m_particleOffsetX*/ - 16);
		//	//m_particles.at(m_particles.size()-1)->setVelocityX(/*getVelocityX()+3.0f*/);
		//}
		//entity->m_particles.at(entity->m_particles.size() - 1)->setY(entity->getY() + entity->getHeight() - entity->m_particles.at(entity->m_particles.size() - 1)->getHeight());
		//entity->m_particles.at(entity->m_particles.size() - 1)->update(0.0f);

		////cRenderingManager::addParticle(entity->m_particles.at(entity->m_particles.size() - 1));
	}
	entity->setVelocityX(0.0f);
	
	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 20.0f) {
		entity->setTimerState(0.0f);
		entity->setIsAttacking(false);		
		//entity->setVelocityY(-5.0f);

		//cSoundsManager::stop(eSoundTag::jump);
		//cSoundsManager::play(eSoundTag::jump);
		
		entity->setState(new cEntityGrodorrJumpState);
	}

}