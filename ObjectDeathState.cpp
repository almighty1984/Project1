#include "ObjectDeathState.h"
#include "ObjectIdleState.h"
#include <iostream>

cObjectDeathState::cObjectDeathState() {
	m_secondCall = false;
}

cObjectDeathState::~cObjectDeathState() {

}

void cObjectDeathState::update(cObject* object, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		object->setTimerState(0.0f);
		object->setIsSolid(false);
		/*if (object->getIsAnimation()) {
			object->setTileOffsetX(0.0f);
		}		*/
	}	

	if (object->getIsAnimation()) {
		/*object->setTileOffsetY(object->getAnimDeath().y);
		object->setAnimationSpeed(object->getAnimDeath().speed);
		object->setAnimationLoops(object->getAnimDeath().loop);*/
		object->setAnimCurrent(object->getAnimDeath());
	}

	object->setTimerState(object->getTimerState() + time);

	if (object->getTimerState() > object->getTimeToBeDead()) {
		object->setTimerState(0);
		object->setState(new cObjectIdleState);
	}
}