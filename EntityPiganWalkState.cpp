#include "EntityPiganWalkState.h"
#include "Player.h"

cEntityPiganWalkState::cEntityPiganWalkState() {
	m_secondCall = false;
}

void cEntityPiganWalkState::update(cApp* app, cEntity* entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setTimerState(0.0f);
		entity->setIsOnBack(false);
	}

	if (entity->getIsFacingLeft()) {
		entity->setVelocityX(-entity->getMoveVelocity());
	} else {
		entity->setVelocityX(entity->getMoveVelocity());
	}
	//entity->m_tileOffsetY = entity->m_animWalk.y;
	//entity->m_animSpeed = entity->m_animWalk.speed;
	entity->setAnim(eAnimTag::walk);
}