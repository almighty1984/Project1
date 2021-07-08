#include "EntityGrodorrJumpState.h"
#include "EntityGrodorrIdleState.h"
#include "EntityGrodorrDeathState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityGrodorrJumpState::cEntityGrodorrJumpState() {
	m_secondCall = false;
}

cEntityGrodorrJumpState::~cEntityGrodorrJumpState() {

}

void cEntityGrodorrJumpState::update(cApp* app, cEntity* entity, float time) {
	if (entity->getVelocityX() < 0) {
		entity->setIsFacingLeft(true);
	} else {
		entity->setIsFacingLeft(false);
	}

	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityGrodorrDeathState);
		return;
	} else {
		entity->setAnim(eAnimTag::jump);
	}
	if (!m_secondCall) {
		m_secondCall = true;
		entity->setIsStunned(false);
		entity->setIsDead(false);
		entity->setVelocityY(-4.0f);
		entity->setTileOffsetX(0.0f);

		if (entity->getSenseCollidedLeft()) {
			entity->setVelocityX(-1.0f);
		} else if (entity->getSenseCollidedRight()) {
			entity->setVelocityX(1.0f);
		} else {
			// Jump in random direction when nobody around
			if (rand() % 2) {
				entity->setVelocityX(0.5f);
			} else {
				entity->setVelocityX(-0.5f);
			}
		}



	}
	if (entity->getVelocityY() >= entity->getFallVelocity()) {
		entity->setVelocityY(entity->getFallVelocity());
		//entity->setVelocityX(0.0f);
	} else {
		entity->setVelocityY(entity->getVelocityY() + entity->getFallAcc() * time);
	}
	//std::cout << "EntityGrodorrJumpState " << entity->getVelocityY() << "\n";
	entity->setAnim(eAnimTag::jump);

	entity->setTimerState(entity->getTimerState() + time);
	if (entity->getTimerState() > 20.0f && entity->getIsOnGround()/* || (entity->getIsInSlope() && entity->getVelocityY() <= 0.2f))*//* && entity->getNumHealth() > 0*/) {
		entity->setTimerState(0);
		entity->setTileOffsetX(0.0f);
		entity->clearSenses();
		//entity->setIsFacingLeft(!entity->getIsFacingLeft());
		entity->setAnim(eAnimTag::attack);
		entity->setState(new cEntityGrodorrIdleState);
	}
}