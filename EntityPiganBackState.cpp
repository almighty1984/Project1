#include "EntityPiganBackState.h"
#include "EntityPiganWalkState.h"
#include "Player.h"

cEntityPiganBackState::cEntityPiganBackState() {

}

cEntityPiganBackState::~cEntityPiganBackState() {

}

void cEntityPiganBackState::update(cApp* app, cEntity* entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTimerState(0.0f);
	}
	
	entity->setIsHurting(true);
	entity->setIsOnBack(true);

	//entity->m_tileOffsetY = entity->m_animWalk.y;
	//entity->m_animSpeed = entity->m_animWalk.speed;
	entity->setAnim(eAnimTag::flipped);


	if (entity->getIsCarried()) {
		entity->setIsOnGround(false);
	}

	if (entity->getIsOnGround()) {
		if (entity->getVelocityX() < 0.0f) {
			entity->setVelocityX(entity->getVelocityX() + entity->getMoveDec());
		} else if (entity->getVelocityX() > 0.0f) {
			entity->setVelocityX(entity->getVelocityX() - entity->getMoveDec());
		}
	}

	entity->setTimerState(entity->getTimerState() + time);
	if (entity->getTimerState() > 200.0f) {
		entity->setState(new cEntityPiganWalkState);
	}
}