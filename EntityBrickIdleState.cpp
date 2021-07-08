#include "EntityBrickIdleState.h"
#include "EntityBrickDeathState.h"
#include <iostream>
#include "Level.h"

cEntityBrickIdleState::cEntityBrickIdleState() {
	m_secondCall = false;
}

cEntityBrickIdleState::~cEntityBrickIdleState() {

}

void cEntityBrickIdleState::update(cApp *app, cEntity *entity, float time) {	
	if (!m_secondCall) {
		std::cout << "cEntityBrickIdleState\n";
		m_secondCall = true;
		entity->setTimerState(0.0f);

		entity->setAnim(eAnimTag::idle);

		entity->setIsFacingLeft(false);
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);

		/*if (entity->getIsDead()) {
			entity->live();
		}*/
		//entity->setIsDead(false);	

		entity->setTimeBeingAlive(0.0f);
		entity->setIsSolid(true);
		//entity->setIsStatic(true);
		entity->setIsCarried(false);
		entity->setIsThrown(false);
		entity->setNumHealth(entity->getStartHealth());


		entity->setStartX(entity->getOldStartX());
		entity->setStartY(entity->getOldStartY());
		
		cLevel* level = entity->getAttachedLevel();

		entity->setX(-level->getX() + entity->getStartX());
		entity->setY(-level ->getY() + entity->getStartY());
		/*entity->setX(l->getReferenceX() + entity->getStartX());
		entity->setY(l->getReferenceY() + entity->getStartY());*/
		/*m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();*/


	}

	//entity->setVelocityX(entity->getVelocityX() * 0.5f);
	
	entity->setIsHidden(false);

	if (entity->getNumHealth() <= 0) {
		entity->setAnim(eAnimTag::death);
		entity->setTileOffsetX(0.0f);
		entity->setState(new cEntityBrickDeathState);
		//return;
	}
	//entity->setTimerState(entity->getTimerState() + time);
}