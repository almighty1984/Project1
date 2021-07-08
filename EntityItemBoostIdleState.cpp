#include "EntityItemBoostIdleState.h"
#include "EntityItemBoostDeadState.h"
//#include "Player.h"
#include "SoundsManager.h"


cEntityItemBoostIdleState::cEntityItemBoostIdleState() {
	m_secondCall = false;
}

cEntityItemBoostIdleState::~cEntityItemBoostIdleState() {

}

void cEntityItemBoostIdleState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setIsDead(false);
		entity->setVelocityY(0.0f);
	}
	
	entity->setAnim(eAnimTag::idle);
	

	if (entity->getNumHealth() <= 0) {
		entity->setIsDead(true);
		entity->setState(new cEntityItemBoostDeadState);
	}
}