#include "EntityGrevertIdleState.h"
#include "EntityGrevertHideState.h"

cEntityGrevertHideState::cEntityGrevertHideState() {
	m_secondCall = false;
}

cEntityGrevertHideState::~cEntityGrevertHideState() {

}

void cEntityGrevertHideState::update(cApp *app, cEntity *entity, float time) {
	entity->setIsIdle(false);
	if (!m_secondCall) {

		entity->setAnim(eAnimTag::hide);
		entity->setTileOffsetX(0.0f);
		entity->setIsStunned(false);
		entity->setTimerState(0.0f);
		m_secondCall = true;
		entity->setIsDead(false);

		entity->setIsHidden(false);
		entity->setVelocityY(0.0f);
	}

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 10.0f) {
		//std::cout << entity->getTimerState() << "\n";
		entity->setTimerState(0.0f);
		entity->setIsAttacking(false);
		entity->setState(new cEntityGrevertIdleState);
	}
}