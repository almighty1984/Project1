#include "ObjectDeathState.h"
#include "ObjectIdleState.h"
#include <iostream>

cObjectIdleState::cObjectIdleState() {
	m_secondCall = false;
}

cObjectIdleState::~cObjectIdleState() {

}

void cObjectIdleState::update(cObject* object, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		object->setTimerState(0.0f);
		//object->setIsSolid(true);

		/*if (object->getIsAnimation()) {
			object->setTileOffsetX(0.0f);
		}*/			
	}
	
	if (object->getIsAnimation()) {
		//std::cout << object->getType() << std::endl;
		/*object->setTileOffsetY(object->getAnimIdle().y);
		object->setAnimationSpeed(object->getAnimIdle().speed);
		object->setAnimationLoops(object->getAnimIdle().loop);*/
		object->setAnimCurrent(object->getAnimDeath());
	}

	object->setTimerState(object->getTimerState() + time);


	//if (/*object->getIsDead() || */object->getTimerState() > object->getTimeToBeIdle() && object->getTimeToBeIdle() != 0.0f) {
	//	object->setTimerState(0);
	//	object->setState(new cObjectDeathState);
	//}
}