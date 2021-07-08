#include "Object.h"
#include "Entity.h"
#include "EntityGrodorrAttackState.h"
#include "SoundsManager.h"
#include "ParticleSenseFlugan.h"
#include "Player.h"


void cParticleSenseFlugan::collisionReactionX(cBaseObject* object) {

	if (object->getType().substr(0, 4) == "clip") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType().substr(0, 3) == "cam") {
	} else if (object->getType().substr(0, 5) == "door_") {
	} else if (object->getType().substr(0, 8) == "e_bounce") {
	} else if (object->getType() == "e_brick") {
	} else if (object->getType() == "e_flugan") {
	} else if (object->getType() == "e_flyling") {
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_pigan") {
	} else if (object->getType().substr(0, 11) == "e_item") {
	} else if (object->getType().substr(0, 8) == "trigger_") {
	} else if (object->getType().substr(0, 5) == "level") {
	} else if (object->getType().substr(0, 4) == "view") {
	} else if (object->getType().substr(0, 4) == "path") {
	} else if (object->getType().substr(0, 4) == "sign") {
	} else if (object->getType().substr(0, 5) == "slope") {
	} else if (object->getType().substr(0, 5) == "wall_") {
	} else if (object->getType().substr(0, 5) == "water") {
	} else if (object->getType() == "player") {
		m_isDead = true;		

		if (object->getIsInWater()) {
			return;
		}		
		if (m_parent != nullptr) {			
			if (m_velocityX < 0.0f) {
				m_parent->senseCollidedLeft(object);
			} else if (m_velocityX > 0.0f) {
				m_parent->senseCollidedRight(object);
			}			
		}
	} else if (object->getType().substr(0, 7) == "target_") {
		//m_isDead = true;
		if (object->getAnimTag() == eAnimTag::idle) {
			//std::cout << "cParticleSense::collisionReactionX " << object->getAnim().y << "\n";
			m_doRemove = true;
		}
	} else {
		m_isDead = true;
	}
}

void cParticleSenseFlugan::collisionReactionY(cBaseObject *object) {
	collisionReactionX(object);
}