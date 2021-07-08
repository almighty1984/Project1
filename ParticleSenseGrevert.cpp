#include "Object.h"
#include "Entity.h"
#include "EntityGrevertAttackState.h"
#include "SoundsManager.h"
#include "ParticleSenseGrevert.h"
#include "Player.h"


void cParticleSenseGrevert::collisionReactionX(cBaseObject* object) {
	if (m_parent == nullptr || object->getIsInWater()) {
		return;
	}
	//std::cout << object->getType() << "\n";
	if (object->getType() == "clip" || object->getType() == "clip_drop" || object->getType() == "clip_top") {
		return;
	} else if (object->getType().substr(0, 3) == "cam" ||
		object->getType().substr(0, 4) == "door" ||
		object->getType().substr(0, 11) == "e_item" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "path" ||
		object->getType().substr(0, 4) == "sign" ||
		object->getType().substr(0, 5) == "slope" ||
		object->getType().substr(0, 5) == "wall_" ||
		object->getType().substr(0, 5) == "water") {
		return;
	} else if (object->getType() == "clip_ledge_L") {
		return;
		/*if (m_parent->getVelocityX() < 0.0f) {
			m_parent->setVelocityX(-m_parent->getVelocityX());
		}*/
	} else if (object->getType() == "clip_ledge_R") {
		return;
		/*if (m_parent->getVelocityX() > 0.0f) {
			m_parent->setVelocityX(-m_parent->getVelocityX());
		}*/
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType() == "player") {
		if (!object->getIsOnGround()) { return; }
		if (object->getVelocityX() == 0.0f) { return; }
		m_isDead = true;
		
		if (m_velocityX < 0.0f) {
			m_parent->senseCollidedLeft(object);
			m_parent->clearSenseRight();
		} else if (m_velocityX > 0.0f) {
			m_parent->senseCollidedRight(object);
			m_parent->clearSenseLeft();
		}
	} else if (object->getType() == "e_brick" || object->getType() == "e_grodorr" || object->getType() == "e_flugan") {
		return;
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType().substr(0, 7) == "target_") {
		//m_isDead = true;
		if (object->getAnimTag() == eAnimTag::idle) {
			//std::cout << "cParticleSenseGrodorr::collisionReactionX " << object->getAnim().y << "\n";
			m_doRemove = true;
		}
	} else if (object->getType() == "e_flyling") {
		return;
	} else {
		m_isDead = true;
	}
}

void cParticleSenseGrevert::collisionReactionY(cBaseObject* object) {
	collisionReactionX(object);
}