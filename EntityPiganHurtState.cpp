#include "EntityPigan.h"
#include "EntityPiganHurtState.h"
#include "EntityPiganBackState.h"
#include <iostream>

cEntityPiganHurtState::cEntityPiganHurtState() : /*m_hideTimer(0), */m_secondCall(false), m_oldVelocityX(0.0f), m_oldForceXPlayerX(0.0f), m_oldForceYPlayerX(0.0f), m_oldForceXPlayerY(0.0f), m_oldForceYPlayerY(0.0f)
{

}

cEntityPiganHurtState::~cEntityPiganHurtState()
{

}

void cEntityPiganHurtState::update(cApp *app, cEntity *entity, float time)
{	
	if (entity == nullptr) {
		return;
	}

	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTileOffsetX(0.0f);
		entity->setIsOnBack(true);
		entity->setTimerState(0.0f);
	}

	entity->setAnim(eAnimTag::hurt);

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 20.0f) {
		entity->setState(new cEntityPiganBackState);
		std::cout << "new cEntityPiganBackState\n";
	}
}