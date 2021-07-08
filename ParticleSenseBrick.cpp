#include "ParticleSenseBrick.h"
#include <iostream>

void cParticleSenseBrick::collisionReactionX(cBaseObject* object) {
	if (m_parent == nullptr) { return; };
	if (object == m_parent) { return; };
	if (object->getType().substr(0, 4) == "clip") {
		if (object->getMiddleX() < m_parent->getMiddleX()) {
			m_parent->senseCollidedLeft(object);
		} else {
			m_parent->senseCollidedRight(object);
		}
	} else if (object->getType().substr(0, 3) == "cam" ||
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType().substr(0, 11) == "e_item" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "path" ||
		object->getType().substr(0, 4) == "sign" ||
		object->getType().substr(0, 5) == "slope" ||
		object->getType().substr(0, 5) == "wall_" ||
		object->getType().substr(0, 5) == "water") {
		return;
	} else if (object->getType() == "player") {
		return;
	} else if (object->getType() == "e_brick") {		
		if (object->getMiddleX() < getMiddleX()) {
			m_parent->senseCollidedLeft(object);
		}
		if (object->getMiddleX() > getMiddleX()) {
			m_parent->senseCollidedRight(object);
		}
	}
	if (object->getType() == "e_grodorr" || object->getType() == "e_flugan") {
		return;
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType().substr(0, 7) == "target_") {
		return;
	} else if (object->getType() == "e_flyling") {
		return;
	} else {
		return;
	}
}

void cParticleSenseBrick::collisionReactionY(cBaseObject* object) {
	if (m_parent == nullptr) { return; };
	if (object == m_parent) { return; };
	//m_sensedObject = object;
	if (m_parent == nullptr) { return; };
	if (object->getType() == "e_brick") {
		//m_aboveObject = object;
		m_parent->senseCollidedAbove(object);
		/*if (object->getAboveObject() != nullptr && object->getAboveObject()->getAboveObject() != nullptr) {
			m_parent->setAboveObject(object->getAboveObject()->getAboveObject());
		} else  if (object->getAboveObject() != nullptr) {
			m_parent->setAboveObject(object->getAboveObject());
		} else {
			m_parent->setAboveObject(object);
		}*/
	} else if (object->getType() == "player") {
		return;
	}
	
	

	//std::cout << object->getType() << "\n";
}