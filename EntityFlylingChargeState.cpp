#include "EntityFlylingChargeState.h"
#include "EntityFlylingAttackState.h"
#include "EntityFlylingDeathState.h"
#include "SoundsManager.h"
#include "RenderingManager.h"

#include "Particle.h"

#include <math.h>

cEntityFlylingChargeState::cEntityFlylingChargeState() {
	m_secondCall = false;
	//m_parent = nullptr;
}

cEntityFlylingChargeState::~cEntityFlylingChargeState() {
	/*if(m_parent != nullptr)
		cRenderingManager::removeParticle(m_parent->m_particles.at(m_parent->m_particles.size()-1 ));*/
}

void cEntityFlylingChargeState::update(cApp *app, cEntity *entity, float time) {	
	/*if(entity->getIsFacingLeft() == false) {
		entity->setVelocityX(2.0f);
	}
	else {
		entity->setVelocityX(-2.0f);
	}*/

	if (m_secondCall == false) {
		m_secondCall = true;
		entity->setIsAttacking(false);
		std::cout << "FlylingChargeState" << "\n";

		//m_parent = entity;

		if (entity->getAttachedPlayer()->getX()+entity->getAttachedPlayer()->getWidth()/2 < entity->getX()+entity->getWidth()/2) {
			entity->setIsFacingLeft(true);
		} else {
			entity->setIsFacingLeft(false);
		}

		entity->setAnim(eAnimTag::idle);

		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);

		cLevel *level = entity->getAttachedLevel();
		level->addParticle(new cParticle);

		float targetX = entity->getAttachedPlayer()->getX()+entity->getAttachedPlayer()->getWidth()/2-8;
		float targetY = entity->getAttachedPlayer()->getY()+entity->getAttachedPlayer()->getHeight()/2+8;

		std::cout << targetX << " " << targetY << "\n";

		level->getParticleLast()->setX( targetX );
		level->getParticleLast()->setY( targetY );

		double direction = atan2(targetY - entity->getY(), targetX - entity->getX() ) * 180 / 3.141592f;
		entity->setDirection( direction );

		level->getParticleLast()->loadConfig("Data\\Particles\\p_flyling_aim.cfg");
		//cRenderingManager::addParticle(entity->m_particles.at(entity->m_particles.size()-1 ));
	}	
	
	entity->setTimerState( entity->getTimerState() + 1);

	if (entity->getTimerState() > 10) {
		entity->setTimerState(0);
		entity->setIsAttacking(true);
		entity->setIsCharging(false);
		cSoundsManager::play(eSoundTag::flylingAttack);

		entity->setState(new cEntityFlylingAttackState);
	}

	if (entity->getNumHealth() <= 0) {
		entity->setIsDead(true);
		entity->setIsAttacking(false);
		entity->setIsCharging(false);
		entity->setState(new cEntityFlylingDeathState);
	}
}