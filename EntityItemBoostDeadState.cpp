#include "EntityItemBoostDeadState.h"
#include "EntityItemBoostIdleState.h"
#include "SoundsManager.h"


cEntityItemBoostDeadState::cEntityItemBoostDeadState()
{
	m_secondCall = false;
}

cEntityItemBoostDeadState::~cEntityItemBoostDeadState()
{

}

void cEntityItemBoostDeadState::update(cApp *app, cEntity *entity, float time) {
	if (m_secondCall == false) {
		m_secondCall = true;
		//entity->setIsHidden(true);

		//bool tmpBool = entity->getIsFacingLeft();
		entity->setTimerState(0);
		entity->setTileOffsetX(0.0f);
		entity->setTileOffsetY(16.0f);
		//if (entity->getIsFacingLeft() == true) {
		//	entity->setVelocityX(4.5f);
		//	//entity->setIsFacingLeft(false);
		//} else {
		//	entity->setVelocityX(-4.5f);
		//	//entity->setIsFacingLeft(true);
		//}
		//entity->setVelocityY(2.5f);
		std::cout << "cEntityItemBoostDeadState\n";
	}

	entity->setIsHurting(true);
	entity->setAnim(eAnimTag::death);

	entity->setTimerState(entity->getTimerState() + time);

	if (entity->getTimerState() > 100.0f) {
		entity->setTimerState(0.0f);
		entity->setIsDead(false);

		entity->setNumHealth(entity->getStartHealth());

		entity->setState(new cEntityItemBoostIdleState);
	}
}